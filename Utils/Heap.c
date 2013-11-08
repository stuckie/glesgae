#include "Heap.h"
#include "Array.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <stdio.h>

/* TODO:
 * Defragmentation
 * Joining of Free Blocks
 * Splitting blocks to use smaller amounts of freed blocks
*/

typedef enum GAE_HeapState_e {
	GAE_HEAP_ALLOCATED = 0
,	GAE_HEAP_FREE
} GAE_HeapState;

typedef struct GAE_HeapInfo_s {
	unsigned int offset;			/* offset into data */
	size_t size;					/* size of this chunk */
	GAE_HeapState state;			/* state of this chunk */
} GAE_HeapInfo_t;


GAE_Heap_t* GAE_Heap_create(const size_t size) {
	GAE_Heap_t* heap = (GAE_Heap_t*)malloc(sizeof(GAE_Heap_t));
	heap->data = 0;
	heap->allocated = 0U;
	heap->used = 0U;
	heap->info = GAE_Array_create(sizeof(GAE_HeapInfo_t));

	return GAE_Heap_reserve(heap, size);
}

GAE_Heap_t* GAE_Heap_reserve(GAE_Heap_t* heap, const size_t size) {
	if (0 == heap->allocated) { /* Empty heap, just malloc it */
		heap->data = (GAE_BYTE*)malloc(size);
		assert(heap->data);
	}
	else if (size > heap->allocated) { /* we're expanding the heap */
		heap->data = (GAE_BYTE*)realloc(heap->data, size);
		assert(heap->data);
	}
	else if (size > heap->used) { /* length is less than capacity.. see if we can shrink it */
		/* need to try and defrag the heap before attempting this... */
		assert(0);
	}
	else { /* array can't be shrunk */
		assert(size > heap->used);
	}

	heap->allocated = size;

	return heap;
}

void* GAE_Heap_malloc(GAE_Heap_t* heap, const size_t size) {
	unsigned int offset = 0U;
	GAE_HeapInfo_t* info = 0;
	if ((heap->allocated - heap->used) < size) {
		GAE_HeapInfo_t* infoBegin = (GAE_HeapInfo_t*)GAE_Array_begin(heap->info);
		GAE_HeapInfo_t* infoEnd = (GAE_HeapInfo_t*)GAE_Array_end(heap->info);
		GAE_HeapInfo_t* info = infoBegin;
		
		/* Optimisation ideas: run through for exact fits first, then near fits.
		 * Split up larger blocks into smaller blocks
		 */
		for (info = infoBegin; info < infoEnd; ++info) { /* try and find a space */
			if (GAE_HEAP_FREE == info->state) {
				if (size <= info->size) { /* if it's going to fit, just use it.. */
					info->state = GAE_HEAP_ALLOCATED;
					return &heap->data[info->offset];
				}
			}
		}
		
		/* no place to put it, so expand */
		GAE_Heap_reserve(heap, heap->used + size);
	}
	
	offset = heap->used;
	info = (GAE_HeapInfo_t*)malloc(sizeof(GAE_HeapInfo_t));
	info->offset = offset;
	info->size = size;
	info->state = GAE_HEAP_ALLOCATED;
	GAE_Array_push(heap->info, (void*)info);
	free(info);
	
	heap->used += size;
	return &heap->data[offset];
}

void* GAE_Heap_get(GAE_Heap_t* heap, const unsigned int index) {
	GAE_HeapInfo_t* info = (GAE_HeapInfo_t*)GAE_Array_get(heap->info, index);
	if ((0 == info) || (GAE_HEAP_FREE == info->state))
		return 0;
		
	return &heap->data[info->offset];
}

unsigned int GAE_Heap_size(GAE_Heap_t* heap) {
	return GAE_Array_size(heap->info);
}

GAE_Heap_t* GAE_Heap_freeIndex(GAE_Heap_t* heap, const unsigned int index) {
	GAE_HeapInfo_t* info = (GAE_HeapInfo_t*)GAE_Array_get(heap->info, index);
	info->state = GAE_HEAP_FREE;
	
	return heap;
}

GAE_Heap_t* GAE_Heap_free(GAE_Heap_t* heap, void* ptr) {
	GAE_HeapInfo_t* infoBegin = (GAE_HeapInfo_t*)GAE_Array_begin(heap->info);
	GAE_HeapInfo_t* infoEnd = (GAE_HeapInfo_t*)GAE_Array_end(heap->info);
	GAE_HeapInfo_t* info = infoBegin;
	
	for (info = infoBegin; info < infoEnd; ++info) {
		if (ptr == &heap->data[info->offset]) {
			info->state = GAE_HEAP_FREE;
			return heap;
		}
	}
	
	/* should probably assert here */
	return heap;
}

void GAE_Heap_delete(GAE_Heap_t* heap) {
	free(heap->data);
	free(heap);
}
