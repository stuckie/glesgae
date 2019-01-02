#ifndef _STATE_H_
#define _STATE_H_

#include "../GAE_Types.h"

struct GAE_Platform_s;

typedef GAE_BOOL (*GAE_State_update_t)(struct GAE_Platform_s* _platform, void* _userData);

typedef struct GAE_State_s {
	GAE_HashString_t id;
	GAE_State_update_t update;
	void* userData;
} GAE_State_t;

GAE_State_t* GAE_State_create(const GAE_HashString_t _id, GAE_State_update_t _update, void* _userData);
void GAE_State_delete(GAE_State_t* _state);

#endif

