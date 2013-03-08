#if defined(LINUX) || defined(PANDORA)

#include "../../Graphics/Window/X11/X11RenderWindow.h"
#include "../EventSystem.h"
#include "../EventTypes.h"
#include "../SystemEvents.h"
#include "X11Events.h"

#include <X11/Xlib.h>

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

	// Register X11 Specific Events
	registerEventType(X11Events::Input::Mouse::Moved);
	registerEventType(X11Events::Input::Mouse::ButtonDown);
	registerEventType(X11Events::Input::Mouse::ButtonUp);

	registerEventType(X11Events::Input::Keyboard::KeyDown);
	registerEventType(X11Events::Input::Keyboard::KeyUp);
}

EventSystem::~EventSystem()
{

}

void EventSystem::bindToWindow(RenderWindow* const window)
{
	mWindow = reinterpret_cast<X11RenderWindow*>(window);
}


void EventSystem::update()
{
	// Deal with the pointer first.
	Window rootReturn;
	Window childReturn;
	int rootXReturn;
	int rootYReturn;
	static int pointerXCurrent = 0;
	static int pointerYCurrent = 0;
	int pointerX;
	int pointerY;
	unsigned int maskReturn;

	if (true == XQueryPointer(mWindow->getDisplay(), mWindow->getWindow()
									, &rootReturn, &childReturn
									, &rootXReturn, &rootYReturn
									, &pointerX, &pointerY, &maskReturn)) {
		if ((pointerX != pointerXCurrent) && (pointerY != pointerYCurrent)) {
			Event* pointerEvent(new X11Events::Input::Mouse::MovedEvent(pointerX, pointerY));
			sendEvent(X11Events::Input::Mouse::Moved, pointerEvent);
			delete pointerEvent;
		}
		pointerXCurrent = pointerX;
		pointerYCurrent = pointerY;
	}

	// Rest of the events...
	XEvent event;
	while (XPending(mWindow->getDisplay())) {
		XNextEvent(mWindow->getDisplay(), &event);

		switch (event.type) {
			case Expose:
				if (event.xexpose.count != 0)
					break;
			break;
			case ConfigureNotify: {
				Event* resizedEvent(new SystemEvents::Window::ResizedEvent(event.xconfigure.width, event.xconfigure.height));
				sendEvent(SystemEvents::Window::Resized, resizedEvent);
				delete resizedEvent;
				}
			break;

			case KeyPress: {
				Event* keydownEvent(new X11Events::Input::Keyboard::KeyDownEvent(XLookupKeysym(&event.xkey, 0)));
				sendEvent(X11Events::Input::Keyboard::KeyDown, keydownEvent);
				delete keydownEvent;
				}
			break;

			case KeyRelease: {
				Event* keyupEvent(new X11Events::Input::Keyboard::KeyUpEvent(XLookupKeysym(&event.xkey, 0)));
				sendEvent(X11Events::Input::Keyboard::KeyUp, keyupEvent);
				delete keyupEvent;
				}
			break;

			case ButtonRelease: {
				Event* buttonupEvent(new X11Events::Input::Mouse::ButtonUpEvent(event.xbutton.button));
				sendEvent(X11Events::Input::Mouse::ButtonUp, buttonupEvent);
				delete buttonupEvent;
				}
			break;

			case ButtonPress: {
				Event* buttondownEvent(new X11Events::Input::Mouse::ButtonDownEvent(event.xbutton.button));
				sendEvent(X11Events::Input::Mouse::ButtonDown, buttondownEvent);
				delete buttondownEvent;
				}
			break;

			case ClientMessage:
				if (static_cast<Atom>(event.xclient.data.l[0]) == mWindow->getDeleteMessage()) {
					Event* windowClosedEvent(new SystemEvents::Window::ClosedEvent);
					Event* appDestroyedEvent(new SystemEvents::App::DestroyedEvent);
					sendEvent(SystemEvents::Window::Closed, windowClosedEvent);
					sendEvent(SystemEvents::App::Destroyed, appDestroyedEvent);
					delete windowClosedEvent;
					delete appDestroyedEvent;
				}

				break;
			default:
				break;
		}
	}
}

#endif

