#ifndef _GROUP_H_
#define _GROUP_H_

#include <stdlib.h>

typedef struct GAE_GroupItem_s {
	struct GAE_GroupItem_s* next;
	void* ptr;
} GAE_GroupItem_t;

typedef struct GAE_Group_s {
	struct GAE_GroupItem_s* begin;
	unsigned int length;
} GAE_Group_t;

GAE_Group_t* GAE_Group_create(void);
GAE_Group_t* GAE_Group_add(GAE_Group_t* group, void* ptr);
GAE_Group_t* GAE_Group_remove(GAE_Group_t* group, void* ptr);
GAE_GroupItem_t* GAE_Group_begin(GAE_Group_t* group);
unsigned int GAE_Group_size(GAE_Group_t* group);
void GAE_Group_delete(GAE_Group_t* group);

#endif
