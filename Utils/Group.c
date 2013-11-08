#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "Group.h"
#include "../GAE_Types.h"

GAE_Group_t* GAE_Group_create(void) {
	GAE_Group_t* group = (GAE_Group_t*)malloc(sizeof(GAE_Group_t));
	group->begin = 0;
	group->length = 0U;

	return group;
}

GAE_Group_t* GAE_Group_add(GAE_Group_t* group, void* ptr) {
	GAE_GroupItem_t* node = group->begin;
	if (0 == node) { /* empty group*/
		node = (GAE_GroupItem_t*)malloc(sizeof(GAE_GroupItem_t));
		assert(node);
		group->begin = node;
	}
	else { /* not empty */
		while (0 != node->next) /* Find next free node */
			node = node->next;

		node->next = (GAE_GroupItem_t*)malloc(sizeof(GAE_GroupItem_t));
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
	
	if (item->ptr == ptr) { /* special case - the first node is the one we're removing */
		free(item);
		group->begin = 0;
	}
	else {
		while (item->next->ptr != ptr) { /* search for the previous node */
			item = item->next;
			assert(item); /* ensure it's a valid pointer, incase we're in the wrong list */
		}

		item->next = item->next->next; /* plug the gap */
		free(item);
	}

	assert(0 < group->length);
	if (0 < group->length)
		--group->length;

	return group;
}

GAE_GroupItem_t* GAE_Group_begin(GAE_Group_t* group) {
	return group->begin;
}

unsigned int GAE_Group_size(GAE_Group_t* group) {
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
