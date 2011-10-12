#include <cstdlib>

#include "X11Events.h"

using namespace GLESGAE;

// Platform Input Events start with 0x2...

EventType X11Events::Input::Mouse::Moved = 			HashString("Input::Mouse::Moved");
EventType X11Events::Input::Mouse::ButtonDown = 	HashString("Input::Mouse::ButtonDown");
EventType X11Events::Input::Mouse::ButtonUp = 		HashString("Input::Mouse::ButtonUp");

EventType X11Events::Input::Keyboard::KeyDown = 	HashString("Input::Keyboard::KeyDown");
EventType X11Events::Input::Keyboard::KeyUp = 		HashString("Input::Keyboard::KeyUp");
