#if defined(ANDROID)

#include "../../Graphics/Window/Android/AndroidRenderWindow.h"
#include "../EventSystem.h"
#include "../EventTypes.h"
#include "../SystemEvents.h"
#include "AndroidEvents.h"

using namespace GLESGAE;

EventSystem::EventSystem()
: CommonEventSystem()
, mActive(true)
, mWindow()
{
	// Register System Events
	registerEventType(SystemEvents::App::Started);
	registerEventType(SystemEvents::App::Paused);
	registerEventType(SystemEvents::App::Resumed);
	registerEventType(SystemEvents::App::Destroyed);

	registerEventType(SystemEvents::Window::Opened);
	registerEventType(SystemEvents::Window::Resized);
	registerEventType(SystemEvents::Window::Closed);

	// Register Android Specific Events
	registerEventType(AndroidEvents::Input::Touch::Moved);
	registerEventType(AndroidEvents::Input::Touch::TouchDown);
	registerEventType(AndroidEvents::Input::Touch::TouchUp);

	registerEventType(AndroidEvents::Input::Keyboard::KeyDown);
	registerEventType(AndroidEvents::Input::Keyboard::KeyUp);
}

EventSystem::~EventSystem()
{

}

void EventSystem::bindToWindow(const Resource<RenderWindow>& window)
{
	mWindow = window.recast<AndroidRenderWindow>();
}


void EventSystem::update()
{

}

#endif

