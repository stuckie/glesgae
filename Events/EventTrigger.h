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
			/// This MUST return 0/NULL on no event.
			virtual Event* hasEvent() = 0;
	};
}

#endif

