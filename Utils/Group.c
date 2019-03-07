#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "Group.h"
#include "../GAE_Types.h"

GAE_Group_t* GAE_Group_create(void) {
	GAE_Group_t* group = malloc(sizeof(GAE_Group_t));
	group->begin = 0;
	group->length = 0U;

	return group;
}

GAE_Group_t* GAE_Group_add(GAE_Group_t* group, void* ptr) {
	GAE_GroupItem_t* node = group->begin;
	if (0 == node) { /* empty group*/
		node = malloc(sizeof(GAE_GroupItem_t));
		assert(node);
		group->begin = node;
	}
	else { /* not empty */
		while (0 != node->next) /* Find next free node */
			node = node->next;

		node->next = malloc(sizeof(GAE_GroupItem_t));
		assert(node);
		node = node->next;
	}

	node->ptr = ptr;
	node->next = 0;

	++group->length;

	return group;
}

GAE_Group_t* GAE_Group_remove(GAE_Group_t* group, void* ptr) {
	GAE_GroupItem_t* begin = group->begin;
	GAE_GroupItem_t* item = begin;
	GAE_GroupItem_t* prev = begin;
	GAE_BOOL isFound = GAE_FALSE;
	
	if (ptr == item->ptr) { /* special case - the first node is the one we're removing */
		group->begin = item->next;
		free(item);
	}
	else {
		while (0 != item) { /* search for next node */
			prev = item;
			item = item->next;
			if (ptr == item->ptr) { 		/* found it */
				prev->next = item->next; 	/* plug the hole */
				free(item);
				isFound = GAE_TRUE;
				break;
			}
		}
		if (GAE_FALSE == isFound)			/* didn't find it */
			return group;					/* just return */
	}

	assert(0 < group->length);
	if (0 < group->length)
		--group->length;

	return group;
}

GAE_GroupItem_t* GAE_Group_begin(GAE_Group_t* group) {
	return group->begin;
}

unsigned int GAE_Group_length(GAE_Group_t* group) {
	return group->length;
}

void GAE_Group_delete(GAE_Group_t* group) {
	GAE_GroupItem_t* item = group->begin;
	GAE_GroupItem_t* self = 0;

	while (0 != item) {
		self = item;
		item = item->next;
		free(self);
	}

	free(group);
}
