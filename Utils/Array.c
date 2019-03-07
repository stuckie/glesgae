#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "Array.h"
#include "../GAE_Types.h"

GAE_Array_t* GAE_Array_create(const unsigned int size) {
	GAE_Array_t* array = malloc(sizeof(GAE_Array_t));
	array->data = 0;
	array->allocated = 0U;
	array->used = 0;
	array->size = size;

	return array;
}

GAE_Array_t* GAE_Array_reserve(GAE_Array_t* array, const unsigned int amount) {
	const unsigned int size = amount * array->size; /* work out size of memory we'll need */

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

GAE_Array_t* GAE_Array_push(GAE_Array_t* array, void* const data) {
	if ((array->allocated - array->used) < array->size)
		GAE_Array_reserve(array, GAE_Array_length(array) + 1U);

	memcpy(&array->data[array->used], data, array->size);
	array->used = array->used + array->size;

	return array;
}

void* GAE_Array_begin(GAE_Array_t* array) {
	return array->data;
}

void* GAE_Array_end(GAE_Array_t* array) {
	return &array->data[array->used];
}

void* GAE_Array_pop(GAE_Array_t* array) {
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

void* GAE_Array_get(GAE_Array_t* array, const unsigned int index) {
	assert((index * array->size) < array->used);
	return &array->data[index * array->size];
}

GAE_Array_t* GAE_Array_delete(GAE_Array_t* array, const unsigned int index) {
	memset(&array->data[index * array->size], 0, array->size);
	return array;
}

unsigned int GAE_Array_length(GAE_Array_t* array) {
	if (0 == array->used)
		return 0;
	else
		return (array->used / array->size);
}

void GAE_Array_destroy(GAE_Array_t* array) {
	free(array->data);
	free(array);
}

