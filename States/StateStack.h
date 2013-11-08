#ifndef _STATE_STACK_H_
#define _STATE_STACK_H_

#include "../GAE_Types.h"

struct GAE_Array_s;
struct GAE_State_s;

typedef struct GAE_StateStack_s {
	struct GAE_Array_s* stack;
	struct GAE_State_s* lastState;
} GAE_StateStack_t;

GAE_StateStack_t* GAE_StateStack_create(void);
GAE_BOOL GAE_StateStack_update(GAE_StateStack_t* stack, const float delta);
struct GAE_State_s* GAE_StateStack_get(GAE_StateStack_t* stack);
GAE_StateStack_t* GAE_StateStack_pop(GAE_StateStack_t* stack);
GAE_StateStack_t* GAE_StateStack_push(GAE_StateStack_t* stack, struct GAE_State_s* state);
GAE_StateStack_t* GAE_StateStack_replace(GAE_StateStack_t* stack, struct GAE_State_s* state);
void GAE_StateStack_delete(GAE_StateStack_t* stack);

#endif
