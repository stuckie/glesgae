#include "EventTypes.h"

using namespace GLESGAE;

// System Events start with 0x1...
// App Events start with 0x11...
// Window Events start with 0x12...

EventType SystemEvents::App::Started = 		0x110000;
EventType SystemEvents::App::Paused = 		0x110001;
EventType SystemEvents::App::Resumed = 		0x110002;
EventType SystemEvents::App::Destroyed = 	0x110003;

EventType SystemEvents::Window::Opened = 	0x120000;
EventType SystemEvents::Window::Resized = 	0x120001;
EventType SystemEvents::Window::Closed = 	0x120002;
