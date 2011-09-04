#ifndef _EVENT_TRIGGER_H_
#define _EVENT_TRIGGER_H_

namespace GLESGAE
{
	class Event;
	class EventTrigger
	{
		public:
			EventTrigger() {}
			virtual ~EventTrigger() {}
			
			/// Check if this trigger has an Event ready.
			/// This MUST return 0 if there is no Event, otherwise it's the event pointer.
			/// This event WILL be cleaned up by the Event System once all Observers have observed the event.
			virtual Event* hasEvent() = 0;
	};
}

#endif

