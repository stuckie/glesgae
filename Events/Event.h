#ifndef _EVENT_H_
#define _EVENT_H_

#include "../Utils/HashString.h"

typedef GAE_HashString_t GAE_EventType_t;
struct GAE_Map_s;

typedef struct GAE_Event_s {
	GAE_EventType_t type;
	struct GAE_Map_s* params;
} GAE_Event_t;

GAE_Event_t* GAE_Event_create(const GAE_EventType_t type, struct GAE_Map_s* const params);
void GAE_Event_delete(GAE_Event_t* event);

#if defined(SDL2)
#include "SDL2/SDL2Events.h"
#elif defined(X11)
#include "X11/X11Events.h"
#elif defined(Android)
#include "Android/AndroidEvents.h"
#endif

#endif

