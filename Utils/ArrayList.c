#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <stdio.h>

#include "ArrayList.h"
#include "../GAE_Types.h"

GAE_ArrayList_t* GAE_ArrayList_create(const size_t size) {
	GAE_ArrayList_t* array = malloc(sizeof(GAE_ArrayList_t));
	array->data = 0;
	array->allocated = 0U;
	array->used = 0;
	array->size = size;

	return array;
}

GAE_ArrayList_t* GAE_ArrayList_reserve(GAE_ArrayList_t* array, const unsigned int amount) {
	const size_t size = amount * array->size; /* work out size of memory we'll need */

	if (0 == array->allocated) { /* Empty array, just malloc it */
		array->data = malloc(size);
		assert(array->data);
	}
	else if (size > array->allocated) { /* we're expanding the array */
		array->data = realloc(array->data, size);
		assert(array->data);
	}
	else if (size > array->used) { /* length is less than capacity.. see if we can shrink it */
		array->data = realloc(array->data, size);
		assert(array->data);
	}
	else { /* array can't be shrunk */
		assert(size > array->used);
	}

	array->allocated = size;

	return array;
}

GAE_ArrayList_t* GAE_ArrayList_push(GAE_ArrayList_t* array, void* const data) {
	if ((array->allocated - array->used) < array->size)
		GAE_ArrayList_reserve(array, GAE_ArrayList_length(array) + 1U);

	memcpy(&array->data[array->used], data, array->size);
	array->used = array->used + array->size;

	return array;
}

void* GAE_ArrayList_peek(GAE_ArrayList_t* array) {
	return &array->data[array->used - array->size];
}

void* GAE_ArrayList_begin(GAE_ArrayList_t* array) {
	return array->data;
}

void* GAE_ArrayList_end(GAE_ArrayList_t* array) {
	return &array->data[array->used];
}

void* GAE_ArrayList_pop(GAE_ArrayList_t* array) {
	void* element = 0;
	if (array->size <= array->used) {
		element = malloc(array->size);
		assert(element);
		memcpy(element, &array->data[array->used - array->size], array->size);
		array->used = array->used - array->size;
	}
	else
		array->used = 0;

	return element;
}

void* GAE_ArrayList_get(GAE_ArrayList_t* array, const unsigned int index) {
	assert((index * array->size) < array->used);
	return &array->data[index * array->size];
}

GAE_ArrayList_t* GAE_ArrayList_remove(GAE_ArrayList_t* array, const unsigned int index) {
	const unsigned int size = GAE_ArrayList_length(array);
	void* temp = GAE_ArrayList_get(array, size - 1U);
	void* current = GAE_ArrayList_get(array, index);
	
	memcpy(current, temp, array->size);
	temp = GAE_ArrayList_pop(array);
	free(temp);
	
	return array;
}

unsigned int GAE_ArrayList_length(GAE_ArrayList_t* array) {
	if (0 == array->used)
		return 0;
	else
		return (array->used / array->size);
}

void GAE_ArrayList_delete(GAE_ArrayList_t* array) {
	free(array->data);
	free(array);
}
