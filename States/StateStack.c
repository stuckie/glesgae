#include "StateStack.h"

#include "../Utils/Array.h"
#include "State.h"

#include <stdlib.h>

GAE_StateStack_t* GAE_StateStack_create(void) {
	GAE_StateStack_t* stack = malloc(sizeof(GAE_StateStack_t));

	stack->stack = GAE_Array_create(sizeof(GAE_State_t));
	stack->lastState = 0;

	return stack;
}

void GAE_StateStack_delete(GAE_StateStack_t* stack) {
	free (stack->stack);
	stack->stack = 0;

	if (0 != stack->lastState)
		free(stack->lastState);
	stack->lastState = 0;

	free(stack);
	stack = 0;
}

GAE_StateStack_t* GAE_StateStack_pop(GAE_StateStack_t* stack) {
	if (0 != stack->lastState)
		free(stack->lastState);

	stack->lastState = GAE_Array_pop(stack->stack);
	return stack;
}

GAE_StateStack_t* GAE_StateStack_push(GAE_StateStack_t* stack, GAE_State_t* state) {
	GAE_Array_push(stack->stack, state);
	return stack;
}

GAE_StateStack_t* GAE_StateStack_replace(GAE_StateStack_t* stack, GAE_State_t* state) {
	free(GAE_Array_pop(stack->stack));
	GAE_Array_push(stack->stack, state);
	return stack;
}

GAE_State_t* GAE_StateStack_get(GAE_StateStack_t* stack) {
	return GAE_Array_get(stack->stack, GAE_Array_size(stack->stack) - 1U);
}

GAE_BOOL GAE_StateStack_update(GAE_StateStack_t* stack, const float delta) {
	GAE_BOOL status = GAE_FALSE;
	GAE_State_t* state = GAE_Array_get(stack->stack, GAE_Array_size(stack->stack) - 1U);
	
	if (0 != state)
		status = (*state->update)(delta, state->userData);
	
	if (0 != stack->lastState) {
		free(stack->lastState);
		stack->lastState = 0;
	}
	
	return status;
}

