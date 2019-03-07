#include "Map.h"

#include "Array.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

GAE_Map_t* GAE_Map_create(const unsigned int keySize, const unsigned int dataSize, GAE_Map_compare_t compare) {
	GAE_Map_t* map = malloc(sizeof(GAE_Map_t));
	assert(map);

	map->ids = GAE_Array_create(keySize);
	map->values = GAE_Array_create(dataSize);
	map->compare = compare;

	assert(map->ids);
	assert(map->values);
	assert(map->compare);

	return map;
}

GAE_Map_t* GAE_Map_reserve(GAE_Map_t* map, const unsigned int amount) {
	GAE_Array_reserve(map->ids, amount);
	GAE_Array_reserve(map->values, amount);

	return map;
}

GAE_Map_t* GAE_Map_push(GAE_Map_t* map, void* const id, void* const data) {
	GAE_Array_push(map->ids, id);
	GAE_Array_push(map->values, data);

	return map;
}

void* GAE_Map_pop(GAE_Map_t* map) {
	void* id = GAE_Array_pop(map->ids);
	free(id);
	return GAE_Array_pop(map->values);
}

void* GAE_Map_get(GAE_Map_t* map, void* const id) {
	void* found = 0;
	unsigned int index = 0U;
	const unsigned int size = GAE_Array_length(map->ids);

	while (index < size) {
		found = GAE_Array_get(map->ids, index);
		if (GAE_TRUE == map->compare(id, found))
			return GAE_Array_get(map->values, index);
		++index;
	}

	return 0;
}

void* GAE_Map_begin(GAE_Map_t* map) {
	if (0 < GAE_Array_length(map->values))
		return GAE_Array_get(map->values, 0);
	else
		return 0;
}

void* GAE_Map_ids(GAE_Map_t* map) {
	if (0 < GAE_Array_length(map->ids))
		return GAE_Array_get(map->ids, 0);
	else
		return 0;
}

GAE_Map_t* GAE_Map_remove(GAE_Map_t* map, void* const id) {
	void* found = 0;
	unsigned int index = 0U;
	const unsigned int size = GAE_Array_length(map->ids);
	void* current = 0;
	void* temp = 0;

	while (index < size) {
		found = GAE_Array_get(map->ids, index);
		if (GAE_TRUE == map->compare(id, found)) { 
			/* copy last element into hole and pop off */
			temp = GAE_Array_get(map->values, size - 1U);
			current = GAE_Array_get(map->values, index);
			memcpy(current, temp, map->values->size);
			temp = GAE_Array_pop(map->values);
			free(temp);

			/* same with ids */
			temp = GAE_Array_get(map->ids, size - 1U);
			memcpy(found, temp, map->ids->size);
			temp = GAE_Array_pop(map->ids);
			free(temp);

			return map;
		}
		++index;
	}

	return map;
}

unsigned int GAE_Map_length(GAE_Map_t* map) {
	return GAE_Array_length(map->ids);
}

void GAE_Map_delete(GAE_Map_t* map) {
	GAE_Array_destroy(map->ids);
	GAE_Array_destroy(map->values);
	free(map);
}
