#include <cstdlib>

#include "X11Events.h"

using namespace GLESGAE;

// Platform Input Events start with 0x2...

EventType X11Events::Input::Mouse::Moved = 			0x210000;
EventType X11Events::Input::Mouse::ButtonDown = 	0x210001;
EventType X11Events::Input::Mouse::ButtonUp = 		0x210002;

EventType X11Events::Input::Keyboard::KeyDown = 	0x220000;
EventType X11Events::Input::Keyboard::KeyUp = 		0x220001;
