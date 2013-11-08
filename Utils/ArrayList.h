#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_

#include <stdlib.h>
#include "../GAE_Types.h"

/* 
An ArrayList is a list masquarading as an array.
Elements will be unordered and muddled about when adding/removing, so don't count on order staying the same.
Use an Array if order is important. An ArrayList if order is not important, but contiguous memory is. Or a List if you're feeling brave.
*/

typedef struct GAE_ArrayList_s {
	GAE_BYTE* data;			/* array data */
	size_t allocated;		/* how much is allocated in array */
	size_t used;			/* how much is used out of allocated array */
	size_t size;			/* size of each element */
} GAE_ArrayList_t;

/* Creates a new ArrayList. */
GAE_ArrayList_t* GAE_ArrayList_create(const size_t size);

/* Creates a contiguous chunk of memory for the specified amount of Array elements. */
GAE_ArrayList_t* GAE_ArrayList_reserve(GAE_ArrayList_t* array, const unsigned int amount);

/* Copies the data into the ArrayList - data can be freed after this call. */
GAE_ArrayList_t* GAE_ArrayList_push(GAE_ArrayList_t* array, void* const data);

/* Returns first element of the array */
void* GAE_ArrayList_begin(GAE_ArrayList_t* array);

/* Returns end of the array */
void* GAE_ArrayList_end(GAE_ArrayList_t* array);

/* Returns a copy of the last element and removes it from the array. This element should be freed after use. */
void* GAE_ArrayList_pop(GAE_ArrayList_t* array);

/* Returns an indexed value of the array. This element should NOT be freed after use. */
void* GAE_ArrayList_get(GAE_ArrayList_t* array, const unsigned int index);

/* Removes an indexed value from the array. */
GAE_ArrayList_t* GAE_ArrayList_remove(GAE_ArrayList_t* array, const unsigned int index);

/* Returns the length of this array in amount of elements with 0 being empty. */
unsigned int GAE_ArrayList_size(GAE_ArrayList_t* array);

/* Deletes the Array and all memory it allocated. Any stray pointers will therefore be undefined. */
void GAE_ArrayList_delete(GAE_ArrayList_t* array);

#endif
