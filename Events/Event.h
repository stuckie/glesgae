#ifndef _EVENT_H_
#define _EVENT_H_

#include "EventTypes.h"

namespace GLESGAE
{
	class Event
	{
		public:
			Event(const EventType& eventType) : mEventType(eventType) {}
			virtual ~Event() {}
			
			/// Get the type of event this is.. useful for classes which mark themselves as EventObservers for multiple Events
			const EventType& getEventType() const { return mEventType; }
			
		private:
			EventType mEventType;
	};
}

#endif

