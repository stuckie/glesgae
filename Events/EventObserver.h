#ifndef _EVENT_OBSERVER_H_
#define _EVENT_OBSERVER_H_

namespace GLESGAE
{
	class Event;
	class EventObserver
	{
		public:
			EventObserver() {}
			virtual ~EventObserver() {}
			
			/// Trigger this Observer to receive an event.
			virtual void receiveEvent(Event* const event) = 0;
	};
}

#endif

