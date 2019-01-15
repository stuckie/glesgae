#ifndef _STATE_STACK_H_
#define _STATE_STACK_H_

#include "../GAE_Types.h"

struct GAE_Array_s;
struct GAE_State_s;

typedef struct GAE_StateStack_s {
	struct GAE_Array_s* stack;
} GAE_StateStack_t;

/* Create a new State Stack */
GAE_StateStack_t* GAE_StateStack_create(void);

/* Update this State Stack */
GAE_BOOL GAE_StateStack_update(GAE_StateStack_t* stack);

/* Gets the current State */
struct GAE_State_s* GAE_StateStack_get(GAE_StateStack_t* stack);

/* Pops the current State */
GAE_StateStack_t* GAE_StateStack_pop(GAE_StateStack_t* stack);

/* Pushes a new State onto the Stack */
GAE_StateStack_t* GAE_StateStack_push(GAE_StateStack_t* stack, struct GAE_State_s* state);

/* Replaces the current running state with the given state */
GAE_StateStack_t* GAE_StateStack_replace(GAE_StateStack_t* stack, struct GAE_State_s* state);

/* Returns if this stack has no states */
GAE_BOOL GAE_StateStack_empty(GAE_StateStack_t* stack);

/* Deletes the Stack */
void GAE_StateStack_delete(GAE_StateStack_t* stack);

#endif
