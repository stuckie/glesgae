#ifndef _SYSTEM_EVENTS_H_
#define _SYSTEM_EVENTS_H_

#include "Event.h"
#include "EventTypes.h"

namespace GLESGAE
{
	namespace SystemEvents
	{
		namespace App
		{
			class StartedEvent : public Event
			{
				public:
					StartedEvent()
					: Event(Started)
					{
						
					}
			};
			
			class PausedEvent : public Event
			{
				public:
					PausedEvent()
					: Event(Paused)
					{
						
					}
			};
			
			class ResumedEvent : public Event
			{
				public:
					ResumedEvent()
					: Event(Resumed)
					{
						
					}
			};
			
			class DestroyedEvent : public Event
			{
				public:
					DestroyedEvent()
					: Event(Destroyed)
					{
						
					}
			};
		}
		
		namespace Window
		{
			class OpenedEvent : public Event
			{
				public:
					OpenedEvent()
					: Event(Opened)
					{
						
					}
			};
			
			class ResizedEvent : public Event
			{
				public:
					ResizedEvent(const int x, const int y)
					: Event(Resized)
					, mX(x)
					, mY(y)
					{
						
					}
					
					/// Return new X dimension
					int getX() const { return mX; }
					
					/// Return new Y dimension
					int getY() const { return mY; }
					
				private:
					int mX;
					int mY;
			};
			
			class ClosedEvent : public Event
			{
				public:
					ClosedEvent()
					: Event(Closed)
					{
						
					}
			};
		}
	}
}

#endif
