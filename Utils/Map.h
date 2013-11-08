#ifndef _MAP_H_
#define _MAP_H_

#include <stdlib.h>
#include "../GAE_Types.h"

typedef GAE_BOOL (*GAE_Map_compare_t)(void* const keyA, void* const keyB);

typedef struct GAE_Map_s {
	struct GAE_Array_s* ids;		/* ids */
	struct GAE_Array_s* values;		/* values */
	GAE_Map_compare_t compare;		/* id compare callback */
} GAE_Map_t;

/* Creates a new Map to store elements of the given size. */
GAE_Map_t* GAE_Map_create(const size_t keySize, const size_t dataSize, GAE_Map_compare_t compare);

/* Creates a contiguous chunk of memory for the specified amount of Array elements. */
GAE_Map_t* GAE_Map_reserve(GAE_Map_t* map, const unsigned int amount);

/* Copies the data into the Map - data can be freed after this call. */
GAE_Map_t* GAE_Map_push(GAE_Map_t* map, void* const id, void* const data);

/* Returns a copy of the last element and removes it from the Map. This element should be freed after use. */
void* GAE_Map_pop(GAE_Map_t* map);

/* Returns an indexed value of the Map. This element should NOT be freed after use. */
void* GAE_Map_get(GAE_Map_t* map, void* const id);

/* Returns a pointer to the first element of the values array. */
void* GAE_Map_begin(GAE_Map_t* map);

/* Returns a pointer to the first element of the ids array. */
void* GAE_Map_ids(GAE_Map_t* map);

/* Removes an element from the Map.*/
GAE_Map_t* GAE_Map_remove(GAE_Map_t* map, void* const id);

/* Returns the length of this Map in amount of elements with 0 being empty. */
unsigned int GAE_Map_size(GAE_Map_t* map);

/* Deletes the Map and all memory it allocated. Any stray pointers will therefore be undefined. */
void GAE_Map_delete(GAE_Map_t* map);

#endif
