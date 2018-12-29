#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "List.h"
#include "../GAE_Types.h"

GAE_SingleList_t* GAE_SingleList_create(const unsigned int size) {
	GAE_SingleList_t* list = (GAE_SingleList_t*)malloc(sizeof(GAE_SingleList_t));
	list->begin = 0;
	list->length = 0U;
	list->size = size;

	return list;
}

GAE_SingleList_t* GAE_SingleList_push(GAE_SingleList_t* list, void* data) {
	GAE_SingleListNode_t* node = list->begin;
	if (0 == node) { /* empty list */
		node = (GAE_SingleListNode_t*)malloc(sizeof(GAE_SingleListNode_t));
		assert(node);
		list->begin = node;
	}
	else { /* not empty */
		while (0 != node->next) /* Find next free node */
			node = node->next;

		node->next = (GAE_SingleListNode_t*)malloc(sizeof(GAE_SingleListNode_t));
		assert(node);
		node = node->next;
	}

	node->data = malloc(list->size);
	assert(node->data);

	memcpy(node->data, data, list->size);
	node->next = 0;

	++list->length;

	return list;
}

GAE_SingleList_t* GAE_SingleList_add(GAE_SingleList_t* list, GAE_SingleListNode_t* node, void* data) {
	GAE_SingleListNode_t* newNode = (GAE_SingleListNode_t*)malloc(sizeof(GAE_SingleListNode_t));
	assert(node);
	assert(newNode);

	newNode->data = malloc(list->size);
	assert(newNode->data);

	memcpy(newNode->data, data, list->size);
	newNode->next = node->next;
	node->next = newNode;

	++list->length;

	return list;
}

GAE_SingleList_t* GAE_SingleList_remove(GAE_SingleList_t* list, GAE_SingleListNode_t* node) {
	GAE_SingleListNode_t* prev = list->begin;

	assert(node);
	if (prev == node) { /* special case - the first node is the one we're removing */
		list->begin = node->next;
		free(node->data);
		free(node);
	}
	else {
		while (prev->next != node) { /* search for the previous node */
			prev = prev->next;
			assert(prev); /* ensure it's a valid pointer, incase we're in the wrong list */
		}

		prev->next = node->next; /* plug the gap */
		free(node->data);
		free(node);
	}

	assert(0 < list->length);
	if (0 < list->length)
		--list->length;

	return list;
}

unsigned int GAE_SingleList_length(GAE_SingleList_t* list) {
	return list->length;
}

void* GAE_SingleList_pop(GAE_SingleList_t* list) {
	GAE_SingleListNode_t* node = list->begin;
	void* data = 0;

	if (0 == node) {
		assert(0 == list->length);
		return node;
	}

	if (0 == node->next) { /* there's only one node in this list */
		data = node->data;
		free(node);
		list->begin = 0;
	}
	else {
		list->begin = node->next;
		data = node->data;
		free(node);
	}

	assert(0 < list->length);
	if (0 < list->length)
		--list->length;

	return data;
}

void GAE_SingleList_delete(GAE_SingleList_t* list) {
	GAE_SingleListNode_t* node = list->begin;
	GAE_SingleListNode_t* prev = 0;

	while (0 != node) {
		free(node->data);
		prev = node;
		node = node->next;
		free(prev);
	}

	free(list);
}


GAE_DoubleList_t* GAE_DoubleList_create(const unsigned int size) {
	GAE_DoubleList_t* list = (GAE_DoubleList_t*)malloc(sizeof(GAE_DoubleList_t));
	list->begin = 0;
	list->end = 0;
	list->length = 0U;
	list->size = size;

	return list;
}

GAE_DoubleList_t* GAE_DoubleList_push(GAE_DoubleList_t* list, void* data) {
	GAE_DoubleListNode_t* prev = list->end;
	GAE_DoubleListNode_t* node = (GAE_DoubleListNode_t*)malloc(sizeof(GAE_DoubleListNode_t));
	assert(node);

	prev->next = node;
	node->prev = prev;

	node->data = malloc(list->size);
	assert(node->data);

	memcpy(node->data, data, list->size);
	node->next = 0;

	++list->length;

	return list;
}

GAE_DoubleList_t* GAE_DoubleList_add(GAE_DoubleList_t* list, GAE_DoubleListNode_t* node, void* data) {
	GAE_DoubleListNode_t* newNode = (GAE_DoubleListNode_t*)malloc(sizeof(GAE_DoubleListNode_t));
	assert(node);
	assert(newNode);

	newNode->data = malloc(list->size);
	assert(newNode->data);

	memcpy(newNode->data, data, list->size);
	newNode->next = node->next;
	node->next = newNode;

	newNode->next->prev = newNode;
	newNode->prev = node;

	++list->length;

	return list;
}

GAE_DoubleList_t* GAE_DoubleList_remove(GAE_DoubleList_t* list, GAE_DoubleListNode_t* node) {
	GAE_DoubleListNode_t* prev = list->begin;

	assert(node);
	if (prev == node) { /* special case - the first node is the one we're removing */
		list->begin = node->next;
		node->prev = 0;
		free(node->data);
		free(node);
	}
	else {
		prev->next = node->next; 	/* plug behind */
		node->prev = prev;			/* plug infront */

		free(node->data);
		free(node);
	}

	assert(0 < list->length);
	if (0 < list->length)
		--list->length;

	return list;
}

unsigned int GAE_DoubleList_length(GAE_DoubleList_t* list) {
	return list->length;
}

void* GAE_DoubleList_pop(GAE_DoubleList_t* list) {
	GAE_DoubleListNode_t* node = list->begin;
	void* data = 0;

	if (0 == node) {
		assert(0 == list->length);
		return node;
	}

	if (0 == node->next) { /* there's only one node in this list */
		data = node->data;
		free(node);
		list->begin = 0;
	}
	else {
		list->begin = node->next;
		node->next->prev = 0;

		data = node->data;
		free(node);
	}

	assert(0 < list->length);
	if (0 < list->length)
		--list->length;

	return data;
}

void GAE_DoubleList_delete(GAE_DoubleList_t* list) {
	GAE_DoubleListNode_t* node = list->begin;
	GAE_DoubleListNode_t* prev = node;

	while (0 != node) {
		free(node->data);
		prev = node;
		node = node->next;
		free(prev);
	}

	free(list);
}
