#ifndef _X11_EVENT_TYPES_H_
#define _X11_EVENT_TYPES_H_

#include "../EventTypes.h"
#include "../Event.h"

#include <X11/Xlib.h>

namespace GLESGAE
{
	namespace X11Events
	{
		namespace Input
		{
			namespace Mouse
			{
				extern EventType Moved;
				extern EventType ButtonDown;
				extern EventType ButtonUp;

				class MovedEvent : public Event
				{
					public:
						MovedEvent(int x, int y)
						: Event(Moved)
						, mX(x)
						, mY(y)
						{

						}

						/// retrieve the new X co-ord
						int getX() const { return mX; }

						/// retrieve the new Y co-ord
						int getY() const { return mY; }

					private:
						int mX;
						int mY;
				};

				class ButtonDownEvent : public Event
				{
					public:
						ButtonDownEvent(unsigned int button)
						: Event(ButtonDown)
						, mButton(button)
						{

						}

						/// retrieve the button pressed
						unsigned int getButton() const { return mButton; }

					private:
						unsigned int mButton;
				};

				class ButtonUpEvent : public Event
				{
					public:
						ButtonUpEvent(unsigned int button)
						: Event(ButtonUp)
						, mButton(button)
						{

						}

						/// retrieve the button released
						unsigned int getButton() const { return mButton; }

					private:
						unsigned int mButton;
				};
			}

			namespace Keyboard
			{
				extern EventType KeyDown;
				extern EventType KeyUp;

				class KeyDownEvent : public Event
				{
					public:
						KeyDownEvent(KeySym key)
						: Event(KeyDown)
						, mKey(key)
						{

						}

						/// retrieve the key pressed
						KeySym getKey() const { return mKey; }

					private:
						KeySym mKey;
				};

				class KeyUpEvent : public Event
				{
					public:
						KeyUpEvent(KeySym key)
						: Event(KeyUp)
						, mKey(key)
						{

						}

						/// retrieve the key released
						KeySym getKey() const { return mKey; }

					private:
						KeySym mKey;
				};
			}
		}
	}
}


#endif
