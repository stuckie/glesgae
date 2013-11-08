#include "EventSystem.h"
#include "../Utils/Array.h"
#include "../Utils/Map.h"

#include <assert.h>
#include <stdio.h>

void GAE_EventSystem_registerObserver(GAE_EventSystem_t* system, const GAE_EventType_t type, GAE_EventObserver_t observer, void* userData) {
	GAE_Array_t* observerArray = 0;
	GAE_EventObserverInfo_t info;

	observerArray = (GAE_Array_t*)GAE_Map_get(system->observers, (void*)&type);
	if (0 == observerArray) {
		observerArray = GAE_Array_create(sizeof(GAE_EventObserverInfo_t));
		GAE_Map_push(system->observers, (void*)&type, observerArray);
		GAE_Array_delete(observerArray);
		observerArray = (GAE_Array_t*)GAE_Map_get(system->observers, (void*)&type);
	}

	info.observer = observer;
	info.userData = userData;
	GAE_Array_push(observerArray, (void*)&info);
}

void GAE_EventSystem_deregisterObserver(GAE_EventSystem_t* system, const GAE_EventType_t type, GAE_EventObserver_t observer) {
	GAE_Array_t* observerArray = 0;
	GAE_EventObserverInfo_t* begin = 0;
	unsigned int index = 0U;
	unsigned int arraySize = 0U;

	observerArray = (GAE_Array_t*)GAE_Map_get(system->observers, (void*)&type);
	assert(observerArray);

	arraySize = GAE_Array_size(observerArray);
	begin = (GAE_EventObserverInfo_t*)GAE_Array_get(observerArray, 0U);
	for (index = 0U; index < arraySize; ++index) {
		if (observer == ((GAE_EventObserverInfo_t*)GAE_Array_get(observerArray, index))->observer) {
			*(begin + index) = *(begin + (arraySize - 1U));
			free(GAE_Array_pop(observerArray));
		}
	}
}

void GAE_EventSystem_registerTrigger(GAE_EventSystem_t* system, const GAE_EventType_t type, GAE_EventTrigger_t trigger, void* userData) {
	GAE_Array_t* triggerArray = 0;
	GAE_EventTriggerInfo_t info;

	triggerArray = (GAE_Array_t*)GAE_Map_get(system->triggers, (void*)&type);
	if (0 == triggerArray) {
		triggerArray = GAE_Array_create(sizeof(GAE_EventTriggerInfo_t));
		GAE_Map_push(system->triggers, (void*)&type, triggerArray);
		GAE_Array_delete(triggerArray);
		triggerArray = (GAE_Array_t*)GAE_Map_get(system->triggers, (void*)&type);
	}

	info.trigger = trigger;
	info.userData = userData;
	GAE_Array_push(triggerArray, (void*)&info);
}

void GAE_EventSystem_deregisterTrigger(GAE_EventSystem_t* system, const GAE_EventType_t type, GAE_EventTrigger_t trigger) {
	GAE_Array_t* triggerArray = 0;
	GAE_EventTriggerInfo_t* begin = 0;
	unsigned int index = 0U;
	unsigned int arraySize = 0U;

	triggerArray = (GAE_Array_t*)GAE_Map_get(system->triggers, (void*)&type);
	assert(triggerArray);

	begin = (GAE_EventTriggerInfo_t*)GAE_Array_get(triggerArray, 0U);
	arraySize = GAE_Array_size(triggerArray);
	for (index = 0U; index < arraySize; ++index) {
		if (trigger == ((GAE_EventTriggerInfo_t*)GAE_Array_get(triggerArray, index))->trigger) {
			*(begin + index) = *(begin + (arraySize - 1U));
			free(GAE_Array_pop(triggerArray));
		}
	}
}

void GAE_EventSystem_sendEvent(GAE_EventSystem_t* system, const GAE_EventType_t type, GAE_Event_t* const event) {
	GAE_Array_t* observerArray = (GAE_Array_t*)GAE_Map_get(system->observers, (void*)&type);
	unsigned int arraySize = 0U;
	GAE_EventObserverInfo_t* observerInfo = 0;
	unsigned int index = 0;

	if (0 == observerArray)
		return;

	arraySize = GAE_Array_size(observerArray);
	assert(type == event->type); /* Sanity Check */
	while (index < arraySize) {
		observerInfo = (GAE_EventObserverInfo_t*)GAE_Array_get(observerArray, index);
		assert(observerInfo);
		(*observerInfo->observer)(event, observerInfo->userData);
		++index;
	}
}

void GAE_EventSystem_updateTriggers(GAE_EventSystem_t* system) {
	/* Outside Array */
	GAE_Array_t* triggerArrayBegin = (GAE_Array_t*)GAE_Map_begin(system->triggers);
	GAE_Array_t* triggerArray = triggerArrayBegin;
	const unsigned int triggerTypeCount = GAE_Map_size(system->triggers);
	unsigned int typeIndex = 0U;

	/* Inside Array */
	GAE_EventTriggerInfo_t* triggerInfo = 0;
	unsigned int triggerIndex = 0U;
	GAE_Event_t* event = 0;

	while (typeIndex < triggerTypeCount) {
		assert(triggerArray);
		triggerIndex = 0;
		triggerInfo = (GAE_EventTriggerInfo_t*)GAE_Array_get(triggerArray, triggerIndex);
		while (0 != triggerInfo) {
			assert(triggerInfo);
			event = (*triggerInfo->trigger)(triggerInfo->userData);
			if (0 != event)
				GAE_EventSystem_sendEvent(system, event->type, event);

			++triggerIndex;
			triggerInfo = (GAE_EventTriggerInfo_t*)GAE_Array_get(triggerArray, triggerIndex);
		}
		++typeIndex;
		triggerArray = triggerArrayBegin + typeIndex;
	}
}
