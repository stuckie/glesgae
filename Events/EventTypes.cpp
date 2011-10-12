#include "EventTypes.h"

using namespace GLESGAE;

EventType SystemEvents::App::Started = 		HashString("App::Started");
EventType SystemEvents::App::Paused = 		HashString("App::Paused");
EventType SystemEvents::App::Resumed = 		HashString("App::Resumed");
EventType SystemEvents::App::Destroyed = 	HashString("App::Destroyed");

EventType SystemEvents::Window::Opened = 	HashString("Window::Opened");
EventType SystemEvents::Window::Resized = 	HashString("Window::Resized");
EventType SystemEvents::Window::Closed = 	HashString("Window::Closed");
