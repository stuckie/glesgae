#include "StateStack.h"

#include "../Utils/Array.h"
#include "State.h"

#include <stdlib.h>

GAE_StateStack_t* GAE_StateStack_create(void)
{
	GAE_StateStack_t* stack = malloc(sizeof(GAE_StateStack_t));

	stack->stack = GAE_Array_create(sizeof(GAE_State_t));

	return stack;
}

void GAE_StateStack_delete(GAE_StateStack_t* stack)
{
	GAE_Array_destroy(stack->stack);
	stack->stack = 0;

	free(stack);
	stack = 0;
}

GAE_StateStack_t* GAE_StateStack_pop(GAE_StateStack_t* stack)
{
	GAE_State_t* state = (GAE_State_t*)GAE_Array_pop(stack->stack);
	free(state);
	return stack;
}

GAE_StateStack_t* GAE_StateStack_push(GAE_StateStack_t* stack, GAE_State_t* state)
{
	GAE_Array_push(stack->stack, state);
	return stack;
}

GAE_StateStack_t* GAE_StateStack_replace(GAE_StateStack_t* stack, GAE_State_t* state)
{
	free(GAE_Array_pop(stack->stack));
	GAE_Array_push(stack->stack, state);
	return stack;
}

GAE_State_t* GAE_StateStack_get(GAE_StateStack_t* stack)
{
	return (GAE_State_t*)GAE_Array_get(stack->stack, GAE_Array_length(stack->stack) - 1U);
}

GAE_BOOL GAE_StateStack_empty(GAE_StateStack_t* stack)
{
	return (0 == GAE_Array_length(stack->stack));
}

GAE_BOOL GAE_StateStack_update(GAE_StateStack_t* stack)
{
	GAE_BOOL status = GAE_FALSE;
	GAE_State_t* state = (GAE_State_t*)GAE_Array_get(stack->stack, GAE_Array_length(stack->stack) - 1U);
	
	if (0 != state)
		status = (*state->update)(state->userData);
	
	return status;
}

