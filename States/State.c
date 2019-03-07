#include "State.h"

#include <stdlib.h>

GAE_State_t* GAE_State_create(const GAE_HashString_t _id, GAE_State_update_t _update, void* _userData)
{
    GAE_State_t* state = malloc(sizeof(GAE_State_t));
    state->id = _id;
    state->update = _update;
    state->userData = _userData;

    return state;
}

void GAE_State_delete(GAE_State_t* _state)
{
    free(_state);
    _state = 0;
}
