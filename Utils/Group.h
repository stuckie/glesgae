#ifndef _GROUP_H_
#define _GROUP_H_

#include <stdlib.h>

/* 
	A Group is a bunch of data that may not necessarily be of the same type or size.
	Particularly useful as a list of pointers to clear up on state change that you don't care what the type is.
	This is effectively a Single Linked List that does not retain ownership of the data.
*/

typedef struct GAE_GroupItem_s {
	struct GAE_GroupItem_s* next;	/* next item in the group */
	void* ptr;						/* pointer to actual data */
} GAE_GroupItem_t;

typedef struct GAE_Group_s {
	struct GAE_GroupItem_s* begin;	/* beginning of the group */
	unsigned int length;			/* current length of the group */
} GAE_Group_t;

/* Create a new Group. */
GAE_Group_t* GAE_Group_create(void);

/* Add an item to this group */
GAE_Group_t* GAE_Group_add(GAE_Group_t* group, void* ptr);

/* Remove an item from this group */
GAE_Group_t* GAE_Group_remove(GAE_Group_t* group, void* ptr);

/* Get the beginning of this group */
GAE_GroupItem_t* GAE_Group_begin(GAE_Group_t* group);

/* Get the length of this group */
unsigned int GAE_Group_length(GAE_Group_t* group);

/* Delete this group */
void GAE_Group_delete(GAE_Group_t* group);

#endif

