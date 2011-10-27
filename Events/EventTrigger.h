#ifndef _EVENT_TRIGGER_H_
#define _EVENT_TRIGGER_H_

#include "../Resources/Resource.h"

namespace GLESGAE
{
	class Event;
	class EventTrigger
	{
		public:
			EventTrigger() {}
			virtual ~EventTrigger() {}
			
			/// Check if this trigger has an Event ready.
			/// This MUST return an empty resource if there is no Event, otherwise it's an Event Resource.
			virtual Resource<Event> hasEvent() = 0;
	};
}

#endif

