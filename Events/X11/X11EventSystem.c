#include "../EventSystem.h"
#include "../Event.h"
#include "../../Graphics/Window/X11/X11RenderWindow.h"

#include "../../Utils/Map.h"
#include "../../Utils/Array.h"

#include <X11/Xlib.h>
#include <assert.h>
#include <stdlib.h>

typedef struct GAE_X11_EventSystem_s {
	GAE_X11_RenderWindow_t* window;
	int pointerXCurrent;
	int pointerYCurrent;
} GAE_X11_EventSystem_t;

void sendPointerEvent(GAE_EventSystem_t* system, const int pointerX, const int pointerY);
void sendResizeEvent(GAE_EventSystem_t* system, const int width, const int height);
void sendKeyPressEvent(GAE_EventSystem_t* system, const KeySym key);
void sendKeyReleaseEvent(GAE_EventSystem_t* system, const KeySym key);
void sendButtonReleaseEvent(GAE_EventSystem_t* system, const unsigned int button);
void sendButtonPressEvent(GAE_EventSystem_t* system, const unsigned int button);
void sendWindowClosedEvent(GAE_EventSystem_t* system);
void sendAppDestroyedEvent(GAE_EventSystem_t* system);

GAE_EventSystem_t* GAE_EventSystem_create(void) {
	GAE_EventSystem_t* system = malloc(sizeof(GAE_EventSystem_t));
	GAE_X11_EventSystem_t* userData = malloc(sizeof(GAE_EventSystem_t));

	userData->window = 0;
	userData->pointerXCurrent = 0;
	userData->pointerYCurrent = 0;
	system->userData = (void*)userData;
	system->observers = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(GAE_Array_t), GAE_HashString_compare);
	system->triggers = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(GAE_Array_t), GAE_HashString_compare);

	return system;
}

void GAE_X11_EventSystem_Bind_Window(GAE_EventSystem_t* commonSystem, GAE_RenderWindow_t* window) {
	GAE_X11_EventSystem_t* system = (GAE_X11_EventSystem_t*)commonSystem->userData;
	system->window = (GAE_X11_RenderWindow_t*)window->platform;
}

void GAE_EventSystem_update(GAE_EventSystem_t* commonSystem) {
	GAE_X11_EventSystem_t* system = (GAE_X11_EventSystem_t*)commonSystem->userData;
	GAE_X11_RenderWindow_t* window = system->window;
	
	Window rootReturn;
	Window childReturn;
	int rootXReturn;
	int rootYReturn;
	int pointerX;
	int pointerY;
	unsigned int maskReturn;

	XEvent xEvent;

	assert(window);

	if (1 == XQueryPointer(window->display, window->window
									, &rootReturn, &childReturn
									, &rootXReturn, &rootYReturn
									, &pointerX, &pointerY, &maskReturn)) {
		if ((pointerX != system->pointerXCurrent) && (pointerY != system->pointerYCurrent))
			sendPointerEvent(commonSystem, pointerX, pointerY);

		system->pointerXCurrent = pointerX;
		system->pointerYCurrent = pointerY;
	}

	while (XPending(window->display)) {
		XNextEvent(window->display, &xEvent);

		switch (xEvent.type) {
			case Expose:
				if (xEvent.xexpose.count != 0)
					break;
			break;
			case ConfigureNotify: {
				sendResizeEvent(commonSystem, xEvent.xconfigure.width, xEvent.xconfigure.width);
				}
			break;

			case KeyPress: {
				sendKeyPressEvent(commonSystem, XLookupKeysym(&xEvent.xkey, 0));
				}
			break;

			case KeyRelease: {
				sendKeyReleaseEvent(commonSystem, XLookupKeysym(&xEvent.xkey, 0));
				}
			break;

			case ButtonRelease: {
				sendButtonReleaseEvent(commonSystem, xEvent.xbutton.button);
				}
			break;

			case ButtonPress: {
				sendButtonPressEvent(commonSystem, xEvent.xbutton.button);
				}
			break;

			case ClientMessage:
				if ((Atom)xEvent.xclient.data.l[0] == window->deleteMessage) {
					sendWindowClosedEvent(commonSystem);
					sendAppDestroyedEvent(commonSystem);
				}

				break;
			default:
				break;
		}
	}
}

void GAE_EventSystem_delete(GAE_EventSystem_t* system) {
	unsigned int observerSize = GAE_Map_length(system->observers);
	unsigned int triggerSize = GAE_Map_length(system->triggers);

	while (0 < observerSize) {
		GAE_Array_destroy((GAE_Array_t*)GAE_Map_pop(system->observers));
		observerSize = GAE_Map_length(system->observers);
	}

	while (0 < triggerSize) {
		GAE_Array_destroy((GAE_Array_t*)GAE_Map_pop(system->triggers));
		triggerSize = GAE_Map_length(system->triggers);
	}

	GAE_Map_delete(system->observers);
	GAE_Map_delete(system->triggers);

	if (0 != system->userData) {
		free(system->userData);
		system->userData = 0;
	}

	system->observers = 0;
	system->triggers = 0;

	free(system);
	system = 0;
}

void sendPointerEvent(GAE_EventSystem_t* system, const int pointerX, const int pointerY) {
	GAE_HashString_t type = GAE_HashString_create("Input::Mouse::Moved");
	GAE_HashString_t id = 0;
	GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(int), GAE_HashString_compare);
	GAE_Event_t* event = 0;

	id = GAE_HashString_create("x");
	GAE_Map_push(params, (void*)&id, (void*)&pointerX);
	id = GAE_HashString_create("y");
	GAE_Map_push(params, (void*)&id, (void*)&pointerY);
	event = GAE_Event_create(type, params);
	
	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}

void sendResizeEvent(GAE_EventSystem_t* system, const int width, const int height) {
	GAE_HashString_t type = GAE_HashString_create("Window::Resized");
	GAE_HashString_t id = 0;
	GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(int), GAE_HashString_compare);
	GAE_Event_t* event = 0;

	id = GAE_HashString_create("width");
	GAE_Map_push(params, (void*)&id, (void*)&width);
	id = GAE_HashString_create("height");
	GAE_Map_push(params, (void*)&id, (void*)&height);
	event = GAE_Event_create(type, params);
	
	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}

void sendKeyPressEvent(GAE_EventSystem_t* system, const KeySym key) {
	GAE_HashString_t type = GAE_HashString_create("Input::Key::Press");
	GAE_HashString_t id = 0;
	GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(KeySym), GAE_HashString_compare);
	GAE_Event_t* event = 0;

	id = GAE_HashString_create("key");
	GAE_Map_push(params, (void*)&id, (void*)&key);
	event = GAE_Event_create(type, params);
	
	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}

void sendKeyReleaseEvent(GAE_EventSystem_t* system, const KeySym key) {
	GAE_HashString_t type = GAE_HashString_create("Input::Key::Release");
	GAE_HashString_t id = 0;
	GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(KeySym), GAE_HashString_compare);
	GAE_Event_t* event = 0;

	id = GAE_HashString_create("key");
	GAE_Map_push(params, (void*)&id, (void*)&key);
	event = GAE_Event_create(type, params);
	
	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}

void sendButtonReleaseEvent(GAE_EventSystem_t* system, const unsigned int button) {
	GAE_HashString_t type = GAE_HashString_create("Input::Mouse::ButtonRelease");
	GAE_HashString_t id = 0;
	GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(unsigned int), GAE_HashString_compare);
	GAE_Event_t* event = 0;

	id = GAE_HashString_create("button");
	GAE_Map_push(params, (void*)&id, (void*)&button);
	event = GAE_Event_create(type, params);
	
	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}

void sendButtonPressEvent(GAE_EventSystem_t* system, const unsigned int button) {
	GAE_HashString_t type = GAE_HashString_create("Input::Mouse::ButtonPress");
	GAE_HashString_t id = 0;
	GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(unsigned int), GAE_HashString_compare);
	GAE_Event_t* event = 0;

	id = GAE_HashString_create("button");
	GAE_Map_push(params, (void*)&id, (void*)&button);
	event = GAE_Event_create(type, params);
	
	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}

void sendWindowClosedEvent(GAE_EventSystem_t* system) {
	GAE_HashString_t type = GAE_HashString_create("Window::Closed");
	GAE_Map_t* params = 0;
	GAE_Event_t* event = 0;

	event = GAE_Event_create(type, params);
	
	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}

void sendAppDestroyedEvent(GAE_EventSystem_t* system) {
	GAE_HashString_t type = GAE_HashString_create("App::Destroyed");
	GAE_Map_t* params = 0;
	GAE_Event_t* event = 0;

	event = GAE_Event_create(type, params);
	
	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}
