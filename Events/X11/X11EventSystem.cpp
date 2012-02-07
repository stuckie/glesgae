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

void EventSystem::bindToWindow(const Resource<RenderWindow>& window)
{
	mWindow = window.recast<X11RenderWindow>();
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
		if ((pointerX != pointerXCurrent) && (pointerY != pointerYCurrent))
			sendEvent(X11Events::Input::Mouse::Moved, Resource<Event>(new X11Events::Input::Mouse::MovedEvent(pointerX, pointerY)));
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
			case ConfigureNotify:
				sendEvent(SystemEvents::Window::Resized, Resource<Event>(new SystemEvents::Window::ResizedEvent(event.xconfigure.width, event.xconfigure.height)));
				break;

			case KeyPress:
				sendEvent(X11Events::Input::Keyboard::KeyDown, Resource<Event>(new X11Events::Input::Keyboard::KeyDownEvent(XLookupKeysym(&event.xkey, 0))));
				break;

			case KeyRelease:
				sendEvent(X11Events::Input::Keyboard::KeyUp, Resource<Event>(new X11Events::Input::Keyboard::KeyUpEvent(XLookupKeysym(&event.xkey, 0))));
				break;

			case ButtonRelease:
				sendEvent(X11Events::Input::Mouse::ButtonUp, Resource<Event>(new X11Events::Input::Mouse::ButtonUpEvent(event.xbutton.button)));
				break;

			case ButtonPress:
				sendEvent(X11Events::Input::Mouse::ButtonDown, Resource<Event>(new X11Events::Input::Mouse::ButtonDownEvent(event.xbutton.button)));
				break;

			case ClientMessage:
				if (static_cast<Atom>(event.xclient.data.l[0]) == mWindow->getDeleteMessage()) {
					sendEvent(SystemEvents::Window::Closed, Resource<Event>(new SystemEvents::Window::ClosedEvent));
					sendEvent(SystemEvents::App::Destroyed, Resource<Event>(new SystemEvents::App::DestroyedEvent));
				}

				break;
			default:
				break;
		}
	}
}

#endif

