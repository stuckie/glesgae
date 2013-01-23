#ifndef _ANDROID_EVENT_TYPES_H_
#define _ANDROID_EVENT_TYPES_H_

#include "../EventTypes.h"
#include "../Event.h"

namespace GLESGAE
{
	namespace AndroidEvents
	{
		namespace Input
		{
			namespace Touch
			{
				extern EventType Moved;
				extern EventType TouchDown;
				extern EventType TouchUp;

				class MovedEvent : public Event
				{
					public:
						MovedEvent(int id, int x, int y)
						: Event(Moved)
						, mId(id)
						, mX(x)
						, mY(y)
						{

						}
						
						/// retrieve the id of this touch
						int getId() const { return mId; }

						/// retrieve the new X co-ord
						int getX() const { return mX; }

						/// retrieve the new Y co-ord
						int getY() const { return mY; }

					private:
						int mId;
						int mX;
						int mY;
				};

				class TouchDownEvent : public Event
				{
					public:
						TouchDownEvent(int id)
						: Event(TouchDown)
						, mId(id)
						{

						}

						/// retrieve the id of this touch
						int getId() const { return mId; }

					private:
						int mId;
				};

				class TouchUpEvent : public Event
				{
					public:
						TouchUpEvent(int id)
						: Event(TouchUp)
						, mId(id)
						{

						}

						/// retrieve the id of this touch
						int getId() const { return mId; }

					private:
						int mId;
				};
			}

			namespace Keyboard
			{
				extern EventType KeyDown;
				extern EventType KeyUp;

				class KeyDownEvent : public Event
				{
					public:
						KeyDownEvent(int key)
						: Event(KeyDown)
						, mKey(key)
						{

						}

						/// retrieve the key pressed
						int getKey() const { return mKey; }

					private:
						int mKey;
				};

				class KeyUpEvent : public Event
				{
					public:
						KeyUpEvent(int key)
						: Event(KeyUp)
						, mKey(key)
						{

						}

						/// retrieve the key released
						int getKey() const { return mKey; }

					private:
						int mKey;
				};
			}
		}
	}
}


#endif
