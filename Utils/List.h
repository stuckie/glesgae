#ifndef _LIST_H_
#define _LIST_H_

/*
	Single Linked List and Double Linked List constrcuts.
	Both of these will own the data they represent.
	If you want a Single Linked List that does not own data, nor care of sizes, use a Group
*/

/* Single Linked List Node */
typedef struct GAE_SingleListNode_s {
	struct GAE_SingleListNode_s* next;
	void* data;
} GAE_SingleListNode_t;

/* Single Linked List construct */
typedef struct GAE_SingleList_s {
	struct GAE_SingleListNode_s* begin;
	unsigned int length;
	unsigned int size;
} GAE_SingleList_t;

/* Create a new linked list with elements of the given size */
GAE_SingleList_t* GAE_SingleList_create(const unsigned int size);

/* Push a new datum to the end of the list. The data is copied so can be freed after this call */
GAE_SingleList_t* GAE_SingleList_push(GAE_SingleList_t* list, void* data);

/* Add a new datum to the list after the given node. The data is copied so can be freed after this call */
GAE_SingleList_t* GAE_SingleList_add(GAE_SingleList_t* list, GAE_SingleListNode_t* node, void* data);

/* Removes the data at the given node. This will free the data */
GAE_SingleList_t* GAE_SingleList_remove(GAE_SingleList_t* list, GAE_SingleListNode_t* node);

/* Returns the length of the given list */
unsigned int GAE_SingleList_length(GAE_SingleList_t* list);

/* Pops off a datum from the front of the list. This will return the data and lose ownership. */
void* GAE_SingleList_pop(GAE_SingleList_t* list);

/* Deletes the entire list and all data it contains */
void GAE_SingleList_delete(GAE_SingleList_t* list);

/* Double Linked List Node */
typedef struct GAE_DoubleListNode_s {
	struct GAE_DoubleListNode_s* next;
	struct GAE_DoubleListNode_s* prev;
	void* data;
} GAE_DoubleListNode_t;

/* Double Linked List Construct */
typedef struct GAE_DoubleList_s {
	struct GAE_DoubleListNode_s* begin;
	struct GAE_DoubleListNode_s* end;
	unsigned int length;
	unsigned int size;
} GAE_DoubleList_t;

/* Create a new Double Linked List contain data of the given size */
GAE_DoubleList_t* GAE_DoubleList_create(const unsigned int size);

/* Pushes a new datum to the end of the list. This copies the data, which can be freed after the call. */
GAE_DoubleList_t* GAE_DoubleList_push(GAE_DoubleList_t* list, void* data);

/* Adds a new datum after the given node. This copies the data, which can be freed after the call. */
GAE_DoubleList_t* GAE_DoubleList_add(GAE_DoubleList_t* list, GAE_DoubleListNode_t* node, void* data);

/* Removes the data at the given node. This will free the data */
GAE_DoubleList_t* GAE_DoubleList_remove(GAE_DoubleList_t* list, GAE_DoubleListNode_t* node);

/* Returns the length of the given list */
unsigned int GAE_DoubleList_length(GAE_DoubleList_t* list);

/* Pops off a datum from the front of the list. This will return the data and lose ownership */
void* GAE_DoubleList_pop(GAE_DoubleList_t* list);

/* Deletes the entire list and all data it contains */
void GAE_DoubleList_delete(GAE_DoubleList_t* list);

#endif
