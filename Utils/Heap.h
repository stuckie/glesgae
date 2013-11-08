#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdlib.h>
#include "../GAE_Types.h"

struct GAE_Array_s;

typedef struct GAE_Heap_s {
	GAE_BYTE* data;					/* heap data */
	size_t allocated;				/* how much is allocated in array */
	size_t used;					/* how much is used out of allocated array */
	struct GAE_Array_s* info;		/* array of info objects */
} GAE_Heap_t;

/* Creates a new Heap of the given size. */
GAE_Heap_t* GAE_Heap_create(const size_t size);

/* Grows the heap to the given size if possible. */
GAE_Heap_t* GAE_Heap_reserve(GAE_Heap_t* heap, const size_t size);

/* Returns a pointer to a new chunk of memory, and ensures there's enough space for it */
void* GAE_Heap_malloc(GAE_Heap_t* heap, const size_t size);

/* Returns an indexed value of the heap. This element should NOT be freed after use. If this element has been freed, it'll return null. */
void* GAE_Heap_get(GAE_Heap_t* heap, const unsigned int index);

/* Returns how many objects are in this heap. This will include freed elements, so if using in a loop, check get for null! */
unsigned int GAE_Heap_size(GAE_Heap_t* heap);

/* Frees a specific element of memory from this heap */
GAE_Heap_t* GAE_Heap_freeIndex(GAE_Heap_t* heap, const unsigned int index);

/* Frees an element of memory from this heap via pointer */
GAE_Heap_t* GAE_Heap_free(GAE_Heap_t* heap, void* ptr);

/* Deletes this heap */
void GAE_Heap_delete(GAE_Heap_t* heap);

#endif
