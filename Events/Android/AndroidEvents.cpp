#include "AndroidEvents.h"

using namespace GLESGAE;

// Platform Input Events start with 0x2...

EventType AndroidEvents::Input::Touch::Moved = 			HashString("Input::Touch::Moved");
EventType AndroidEvents::Input::Touch::TouchDown =	 	HashString("Input::Touch::TouchDown");
EventType AndroidEvents::Input::Touch::TouchUp = 		HashString("Input::Touch::TouchUp");

EventType AndroidEvents::Input::Keyboard::KeyDown = 	HashString("Input::Keyboard::KeyDown");
EventType AndroidEvents::Input::Keyboard::KeyUp = 		HashString("Input::Keyboard::KeyUp");
