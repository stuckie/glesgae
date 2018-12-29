#ifndef _EVENT_SYSTEM_H_
#define _EVENT_SYSTEM_H_

#include "Event.h"

/** Event System

The Event System has been simplified immensely from it's original C++ design.
An Event System datum can be created via _create, and must be removed by the corresponding _delete function.
The datum itself contains a map of observers and triggers. The key being the Event Type, and the value being an array of Info data.
When an Observer or Trigger callback is made, the user data that was specified on creation of the callback is sent with it.

The update function is platform specific and is defined in each platform's EventSystem.c
**/

struct GAE_Map_s;

typedef GAE_Event_t* (*GAE_EventTrigger_t)(void* userData);
typedef void (*GAE_EventObserver_t)(struct GAE_Event_s* const event, void* userData);

typedef struct GAE_EventObserverInfo_s {
	GAE_EventObserver_t observer;
	void* userData;
} GAE_EventObserverInfo_t;

typedef struct GAE_EventTriggerInfo_s {
	GAE_EventTrigger_t trigger;
	void* userData;
} GAE_EventTriggerInfo_t;

typedef struct GAE_EventSystem_s {
	struct GAE_Map_s* observers;
	struct GAE_Map_s* triggers;
	void* userData;
} GAE_EventSystem_t;

/* Platform specific create function - binds to the specified Window for window events */
GAE_EventSystem_t* GAE_EventSystem_create(void);

/* Update the Platform specific Event System */
void GAE_EventSystem_update(GAE_EventSystem_t* system);

/* Update the triggers - to be called via the platform specific update */
void GAE_EventSystem_updateTriggers(GAE_EventSystem_t* system);

/* Platform specific delete function */
void GAE_EventSystem_delete(GAE_EventSystem_t* system);

/* Register an Observer of the given Event Type on the requested system, and pass the userDatum when it is triggered */
void GAE_EventSystem_registerObserver(GAE_EventSystem_t* system, const GAE_EventType_t type, GAE_EventObserver_t observer, void* userData);

/* Deregister this observer from the given Event Type on this system */
void GAE_EventSystem_deregisterObserver(GAE_EventSystem_t* system, const GAE_EventType_t type, GAE_EventObserver_t observer);

/* Register a Trigger of the given Event Type on the requested system, and pass the userDatum when it is triggered */
void GAE_EventSystem_registerTrigger(GAE_EventSystem_t* system, const GAE_EventType_t type, GAE_EventTrigger_t trigger, void* userData);

/* Deregister this trigger from the given Event Type on this system */
void GAE_EventSystem_deregisterTrigger(GAE_EventSystem_t* system, const GAE_EventType_t type, GAE_EventTrigger_t trigger);

/* Send an Event to this Event System */
void GAE_EventSystem_sendEvent(GAE_EventSystem_t* system, GAE_Event_t* const event);

#endif
