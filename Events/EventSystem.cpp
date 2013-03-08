#include <vector>
#include <map>
#include <cstdio>

#include "Event.h"
#include "EventObserver.h"
#include "EventTrigger.h"
#include "EventSystem.h"

using namespace GLESGAE;

void CommonEventSystem::registerEventType(const EventType& eventType)
{
	// Should probably have a sanity check to ensure we don't already have this.
	mEventObservers[eventType] = std::vector<EventObserver*>();
	mEventTriggers[eventType] = std::vector<EventTrigger*>();
}

void CommonEventSystem::registerObserver(const EventType& eventType, EventObserver* const observer)
{
	// Should probably have a sanity check to ensure we don't already have this observer....
	
	// Add it to the array.
	mEventObservers[eventType].push_back(observer);
}

void CommonEventSystem::deregisterObserver(const EventType& eventType, EventObserver* const observer)
{
	std::vector<EventObserver*>& eventArray(mEventObservers[eventType]);
	
	// Can we find it?
	for (std::vector<EventObserver*>::iterator itr(eventArray.begin()); itr < eventArray.end(); ++itr) {
		if (observer == (*itr)) {
			(*itr) = (*(eventArray.end() - 1U));
			eventArray.pop_back();
			return;
		}
	}
	
	printf("EventSystem: tried to deregister an event observer which was not registered.\n");
}

void CommonEventSystem::registerTrigger(const EventType& eventType, EventTrigger* const trigger)
{
	// Should probably sanity check to ensure we don't already have this registered.
	
	// Add it to the array.
	mEventTriggers[eventType].push_back(trigger);
}

void CommonEventSystem::deregisterTrigger(const EventType& eventType, EventTrigger* const trigger)
{
	std::vector<EventTrigger*>& eventArray(mEventTriggers[eventType]);
	
	// Can we find it?
	for (std::vector<EventTrigger*>::iterator itr(eventArray.begin()); itr < eventArray.end(); ++itr) {
		if (trigger == (*itr)) {
			(*itr) = (*(eventArray.end() - 1U));
			eventArray.pop_back();
			return;
		}
	}
	
	printf("EventSystem: tried to deregister an event trigger which was not registered.\n");
}

void CommonEventSystem::sendEvent(const EventType& eventType, Event* const event)
{
	// Quick Sanity Check
	if (eventType != event->getEventType()) {
		printf("EventSystem: tried to send an event of differing type to EventType requested. You bad person.\n");
		return;
	}
	
	std::vector<EventObserver*>& eventArray(mEventObservers[eventType]);
	
	// Send to all Observers in this list.
	for (std::vector<EventObserver*>::iterator itr(eventArray.begin()); itr < eventArray.end(); ++itr)
		(*itr)->receiveEvent(event);
}

void CommonEventSystem::updateAllTriggers()
{
	for (std::map<EventType, std::vector<EventTrigger*> >::iterator eventType(mEventTriggers.begin()); eventType != mEventTriggers.end(); ++eventType) {
		std::vector<EventTrigger*>& eventArray(eventType->second);
		for (std::vector<EventTrigger*>::iterator itr(eventArray.begin()); itr < eventArray.end(); ++itr) {
			Event* const event((*itr)->hasEvent());
			if (event != 0)
				sendEvent(eventType->first, event);
		}
	}
}
