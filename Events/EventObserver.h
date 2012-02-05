#ifndef _EVENT_OBSERVER_H_
#define _EVENT_OBSERVER_H_

#include "../Resources/Resource.h"

namespace GLESGAE
{
	class Event;
	class EventObserver
	{
		public:
			EventObserver() {}
			virtual ~EventObserver() {}
			
			/// Trigger this Observer to receive an event.
			virtual void receiveEvent(const Resource<Event>& event) = 0;
	};
}

#endif

