#include "Event.h"

#include "../Utils/Map.h"

GAE_Event_t* GAE_Event_create(const GAE_EventType_t type, GAE_Map_t* const params) {
	GAE_Event_t* event = (GAE_Event_t*)malloc(sizeof(GAE_Event_t));
	event->type = type;
	event->params = params;

	return event;
}

void GAE_Event_delete(GAE_Event_t* event) {
	if (0 != event->params)
		GAE_Map_delete(event->params);
	event->params = 0;

	free(event);
	event = 0;
}
