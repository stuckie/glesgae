#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

typedef struct GAE_SingleListNode_s {
	struct GAE_SingleListNode_s* next;
	void* data;
} GAE_SingleListNode_t;

typedef struct GAE_SingleList_s {
	struct GAE_SingleListNode_s* begin;
	unsigned int length;
	size_t size;
} GAE_SingleList_t;

GAE_SingleList_t* GAE_SingleList_create(const size_t size);
GAE_SingleList_t* GAE_SingleList_push(GAE_SingleList_t* list, void* data);
GAE_SingleList_t* GAE_SingleList_add(GAE_SingleList_t* list, GAE_SingleListNode_t* node, void* data);
GAE_SingleList_t* GAE_SingleList_remove(GAE_SingleList_t* list, GAE_SingleListNode_t* node);
unsigned int GAE_SingleList_size(GAE_SingleList_t* list);
void* GAE_SingleList_pop(GAE_SingleList_t* list);
void GAE_SingleList_delete(GAE_SingleList_t* list);

typedef struct GAE_DoubleListNode_s {
	struct GAE_DoubleListNode_s* next;
	struct GAE_DoubleListNode_s* prev;
	void* data;
} GAE_DoubleListNode_t;

typedef struct GAE_DoubleList_s {
	struct GAE_DoubleListNode_s* begin;
	struct GAE_DoubleListNode_s* end;
	unsigned int length;
	size_t size;
} GAE_DoubleList_t;

GAE_DoubleList_t* GAE_DoubleList_create(const size_t size);
GAE_DoubleList_t* GAE_DoubleList_push(GAE_DoubleList_t* list, void* data);
GAE_DoubleList_t* GAE_DoubleList_add(GAE_DoubleList_t* list, GAE_DoubleListNode_t* node, void* data);
GAE_DoubleList_t* GAE_DoubleList_remove(GAE_DoubleList_t* list, GAE_DoubleListNode_t* node);
unsigned int GAE_DoubleList_size(GAE_DoubleList_t* list);
void* GAE_DoubleList_pop(GAE_DoubleList_t* list);
void GAE_DoubleList_delete(GAE_DoubleList_t* list);

#endif
