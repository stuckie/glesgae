#ifndef _STATE_H_
#define _STATE_H_

#include "../GAE_Types.h"

typedef GAE_BOOL (*GAE_State_update_t)(const float delta, void* userData);

typedef struct GAE_State_s {
	GAE_HashString_t id;
	GAE_State_update_t* update;
	void* userData;
} GAE_State_t;

GAE_State_t* GAE_State_create(const GAE_HashString_t id, GAE_State_update_t* update, void* userData);
void GAE_State_delete(GAE_State_t* state);

#endif

