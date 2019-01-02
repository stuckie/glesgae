#include "StateStack.h"

#include "../Utils/Array.h"
#include "State.h"

#include <stdlib.h>

GAE_StateStack_t* GAE_StateStack_create(void)
{
	GAE_StateStack_t* stack = (GAE_StateStack_t*)malloc(sizeof(GAE_StateStack_t));

	stack->stack = GAE_Array_create(sizeof(GAE_State_t));
	stack->lastState = 0;

	return stack;
}

void GAE_StateStack_delete(GAE_StateStack_t* _stack)
{
	GAE_Array_delete(_stack->stack);
	_stack->stack = 0;

	if (0 != _stack->lastState)
		free(_stack->lastState);
	_stack->lastState = 0;

	free(_stack);
	_stack = 0;
}

GAE_StateStack_t* GAE_StateStack_pop(GAE_StateStack_t* _stack)
{
	if (0 != _stack->lastState)
		free(_stack->lastState);

	_stack->lastState = (GAE_State_t*)GAE_Array_pop(_stack->stack);
	return _stack;
}

GAE_StateStack_t* GAE_StateStack_push(GAE_StateStack_t* _stack, GAE_State_t* _state)
{
	GAE_Array_push(_stack->stack, _state);
	return _stack;
}

GAE_StateStack_t* GAE_StateStack_replace(GAE_StateStack_t* _stack, GAE_State_t* _state)
{
	free(GAE_Array_pop(_stack->stack));
	GAE_Array_push(_stack->stack, _state);
	return _stack;
}

GAE_State_t* GAE_StateStack_get(GAE_StateStack_t* _stack)
{
	return (GAE_State_t*)GAE_Array_get(_stack->stack, GAE_Array_length(_stack->stack) - 1U);
}

GAE_BOOL GAE_StateStack_update(GAE_StateStack_t* _stack, struct GAE_Platform_s* _platform) {
	GAE_BOOL status = GAE_FALSE;
	GAE_State_t* state = (GAE_State_t*)GAE_Array_get(_stack->stack, GAE_Array_length(_stack->stack) - 1U);
	
	if (0 != state)
		status = (*state->update)(_platform, state->userData);
	
	if (0 != _stack->lastState) {
		free(_stack->lastState);
		_stack->lastState = 0;
	}
	
	return status;
}

