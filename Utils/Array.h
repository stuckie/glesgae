#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "../GAE_Types.h"

typedef struct GAE_Array_s {
	GAE_BYTE* data;			/* array data */
	unsigned int allocated;		/* how much is allocated in array */
	unsigned int used;			/* how much is used out of allocated array */
	unsigned int size;			/* size of each element */
} GAE_Array_t;

/* Creates a new Array. */
GAE_Array_t* GAE_Array_create(const unsigned int size);

/* Creates a contiguous chunk of memory for the specified amount of Array elements. */
GAE_Array_t* GAE_Array_reserve(GAE_Array_t* array, const unsigned int amount);

/* Copies the data into the Array - data can be freed after this call. */
GAE_Array_t* GAE_Array_push(GAE_Array_t* array, void* const data);

/* Returns first element of the array */
void* GAE_Array_begin(GAE_Array_t* array);

/* Returns the end of the array */
void* GAE_Array_end(GAE_Array_t* array);

/* Returns a copy of the last element and removes it from the array. This element should be freed after use. */
void* GAE_Array_pop(GAE_Array_t* array);

/* Returns an indexed value of the array. This element should NOT be freed after use. */
void* GAE_Array_get(GAE_Array_t* array, const unsigned int index);

/* Returns the length of this array in amount of elements with 0 being empty. */
unsigned int GAE_Array_length(GAE_Array_t* array);

/* Deletes the Array and all memory it allocated. Any stray pointers will therefore be undefined. */
void GAE_Array_delete(GAE_Array_t* array);

#endif
