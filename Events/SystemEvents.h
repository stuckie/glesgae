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
					ResizedEvent(const unsigned int width, const unsigned int height)
					: Event(Resized)
					, mWidth(width)
					, mHeight(height)
					{
						
					}
					
					/// Return new Width
					unsigned int getWidth() const { return mWidth; }
					
					/// Return new Height
					unsigned int getHeight() const { return mHeight; }
					
				private:
					unsigned int mWidth;
					unsigned int mHeight;
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
