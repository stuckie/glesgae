#include "../EventSystem.h"
#include "../Event.h"
#include "SDL2Events.h"

#include "../../Utils/Map.h"
#include "../../Utils/Array.h"

#include "SDL2/SDL.h"

void handleWindowEvent(SDL_Event* event, GAE_EventSystem_t* system);
void handleTextEditingEvent(SDL_Event* event, GAE_EventSystem_t* system);
void handleTextInputEvent(SDL_Event* event, GAE_EventSystem_t* system);
void handleQuitEvent(SDL_Event* event, GAE_EventSystem_t* system);
void handleUserEvent(SDL_Event* event, GAE_EventSystem_t* system);
void handleSysWMEvent(SDL_Event* event, GAE_EventSystem_t* system);
void handleDropEvent(SDL_Event* event, GAE_EventSystem_t* system);
void handleAppEvent(SDL_Event* event, GAE_EventSystem_t* system);
void sendEvent(GAE_HashString_t type, SDL_Event* event, GAE_EventSystem_t* system);

GAE_EventSystem_t* GAE_EventSystem_create(void) {
	GAE_EventSystem_t* system = malloc(sizeof(GAE_EventSystem_t));

	system->observers = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(GAE_Array_t), GAE_HashString_compare);
	system->triggers = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(GAE_Array_t), GAE_HashString_compare);
	system->userData = 0;

	GAE_Events_create();

	return system;
}

void GAE_EventSystem_update(GAE_EventSystem_t* system) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_WINDOWEVENT: {
				handleWindowEvent(&event, system);
			}
			break;
			case SDL_KEYUP:
			case SDL_KEYDOWN: {
				sendEvent(GAE_EVENT_KEYBOARD, &event, system);
			}
			break;
			case SDL_TEXTEDITING: {
				handleTextEditingEvent(&event, system);
			}
			break;
			case SDL_TEXTINPUT: {
				handleTextInputEvent(&event, system);
			}
			break;
			case SDL_MOUSEMOTION: {
				sendEvent(GAE_EVENT_MOUSE_MOTION, &event, system);
			}
			break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN: {
				sendEvent(GAE_EVENT_MOUSE_BUTTON, &event, system);
			}
			break;
			case SDL_MOUSEWHEEL: {
				sendEvent(GAE_EVENT_MOUSE_WHEEL, &event, system);
			}
			break;
			case SDL_JOYAXISMOTION: {
				sendEvent(GAE_EVENT_JOYSTICK_AXIS, &event, system);
			}
			break;
			case SDL_JOYBALLMOTION: {
				sendEvent(GAE_EVENT_JOYSTICK_BALL, &event, system);
			}
			break;
			case SDL_JOYHATMOTION: {
				sendEvent(GAE_EVENT_JOYSTICK_HAT, &event, system);
			}
			break;
			case SDL_JOYBUTTONUP:
			case SDL_JOYBUTTONDOWN: {
				sendEvent(GAE_EVENT_JOYSTICK_BUTTON, &event, system);
			}
			break;
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED: {
				sendEvent(GAE_EVENT_JOYSTICK_DEVICE, &event, system);
			}
			break;
			case SDL_CONTROLLERAXISMOTION: {
				sendEvent(GAE_EVENT_CONTROLLER_MOTION, &event, system);
			}
			break;
			case SDL_CONTROLLERBUTTONUP:
			case SDL_CONTROLLERBUTTONDOWN: {
				sendEvent(GAE_EVENT_CONTROLLER_BUTTON, &event, system);
			}
			break;
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMAPPED: {
				sendEvent(GAE_EVENT_CONTROLLER_DEVICE, &event, system);
			}
			break;
			case SDL_QUIT: {
				handleQuitEvent(&event, system);
			}
			break;
			case SDL_USEREVENT: {
				handleUserEvent(&event, system);
			}
			break;
			case SDL_SYSWMEVENT: {
				handleSysWMEvent(&event, system);
			}
			break;
			case SDL_FINGERUP:
			case SDL_FINGERDOWN:
			case SDL_FINGERMOTION: {
				sendEvent(GAE_EVENT_TOUCH, &event, system);
			}
			break;
			case SDL_MULTIGESTURE: {
				sendEvent(GAE_EVENT_MULTIGESTURE, &event, system);
			}
			break;
			case SDL_DOLLARGESTURE:
			case SDL_DOLLARRECORD: {
				sendEvent(GAE_EVENT_DOLLARGESTURE, &event, system);
			}
			break;
			case SDL_DROPFILE: {
				handleDropEvent(&event, system);
			}
			break;
			case SDL_APP_TERMINATING:
			case SDL_APP_LOWMEMORY:
			case SDL_APP_WILLENTERBACKGROUND:
			case SDL_APP_DIDENTERBACKGROUND:
			case SDL_APP_WILLENTERFOREGROUND:
			case SDL_APP_DIDENTERFOREGROUND: {
				handleAppEvent(&event, system);
			}
			default:
			break;
		}
	}
	
	GAE_EventSystem_updateTriggers(system);
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

void sendEvent(GAE_HashString_t type, SDL_Event* sdlEvent, GAE_EventSystem_t* system) {
	GAE_Event_t* event = 0;
	GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(SDL_Event), GAE_HashString_compare);

	GAE_HashString_t id = GAE_HASH_EVENT;
	GAE_Map_push(params, (void*)&id, (void*)sdlEvent);
	event = GAE_Event_create(type, params);

	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}

void sendSimpleEvent(GAE_HashString_t type, GAE_EventSystem_t* system) {
	GAE_Event_t* event = 0;
	GAE_Map_t* params = 0;

	event = GAE_Event_create(type, params);
	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}

void handleWindowEvent(SDL_Event* sdlEvent, GAE_EventSystem_t* system) {
	switch (sdlEvent->window.event) {
		case SDL_WINDOWEVENT_SHOWN:
			sendSimpleEvent(GAE_EVENT_WINDOW_SHOWN, system);
		break;
		case SDL_WINDOWEVENT_HIDDEN:
			sendSimpleEvent(GAE_EVENT_WINDOW_HIDDEN, system);
		break;
		case SDL_WINDOWEVENT_EXPOSED:
			sendSimpleEvent(GAE_EVENT_WINDOW_EXPOSED, system);
		break;
		case SDL_WINDOWEVENT_MOVED: {
			GAE_HashString_t type = GAE_EVENT_WINDOW_MOVED;
			GAE_HashString_t id = 0;
			GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(int), GAE_HashString_compare);
			GAE_Event_t* event = 0;

			id = GAE_HASH_WINDOW;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.windowID));
			id = GAE_HASH_X;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.data1));
			id = GAE_HASH_Y;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.data2));
			event = GAE_Event_create(type, params);

			GAE_EventSystem_sendEvent(system, event);
			GAE_Event_delete(event);
		}
		break;
		case SDL_WINDOWEVENT_RESIZED: {
			GAE_HashString_t type = GAE_EVENT_WINDOW_RESIZED;
			GAE_HashString_t id = 0;
			GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(int), GAE_HashString_compare);
			GAE_Event_t* event = 0;

			id = GAE_HASH_WINDOW;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.windowID));
			id = GAE_HASH_WIDTH;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.data1));
			id = GAE_HASH_HEIGHT;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.data2));
			event = GAE_Event_create(type, params);

			GAE_EventSystem_sendEvent(system, event);
			GAE_Event_delete(event);
		}
		break;
		case SDL_WINDOWEVENT_MINIMIZED:
			sendSimpleEvent(GAE_EVENT_WINDOW_MINIMISED, system);
		break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			sendSimpleEvent(GAE_EVENT_WINDOW_MAXIMISED, system);
		break;
		case SDL_WINDOWEVENT_RESTORED:
			sendSimpleEvent(GAE_EVENT_WINDOW_RESTORED, system);
		break;
		case SDL_WINDOWEVENT_ENTER: {
			GAE_HashString_t type = GAE_EVENT_WINDOW_ENTER;
			GAE_HashString_t id = 0;
			GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(int), GAE_HashString_compare);
			GAE_Event_t* event = 0;

			id = GAE_HASH_WINDOW;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.windowID));
			event = GAE_Event_create(type, params);

			GAE_EventSystem_sendEvent(system, event);
			GAE_Event_delete(event);
		}
		break;
		case SDL_WINDOWEVENT_LEAVE: {
			GAE_HashString_t type = GAE_EVENT_WINDOW_LEAVE;
			GAE_HashString_t id = 0;
			GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(int), GAE_HashString_compare);
			GAE_Event_t* event = 0;

			id = GAE_HASH_WINDOW;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.windowID));
			event = GAE_Event_create(type, params);

			GAE_EventSystem_sendEvent(system, event);
			GAE_Event_delete(event);
		}
		break;
		case SDL_WINDOWEVENT_FOCUS_GAINED: {
			GAE_HashString_t type = GAE_EVENT_FOCUS_GAINED;
			GAE_HashString_t id = 0;
			GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(int), GAE_HashString_compare);
			GAE_Event_t* event = 0;

			id = GAE_HASH_WINDOW;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.windowID));
			event = GAE_Event_create(type, params);

			GAE_EventSystem_sendEvent(system, event);
			GAE_Event_delete(event);
		}
		break;
		case SDL_WINDOWEVENT_FOCUS_LOST: {
			GAE_HashString_t type = GAE_EVENT_FOCUS_LOST;
			GAE_HashString_t id = 0;
			GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(int), GAE_HashString_compare);
			GAE_Event_t* event = 0;

			id = GAE_HASH_WINDOW;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.windowID));
			event = GAE_Event_create(type, params);

			GAE_EventSystem_sendEvent(system, event);
			GAE_Event_delete(event);
		}
		break;
		case SDL_WINDOWEVENT_CLOSE: {
			GAE_HashString_t type = GAE_EVENT_WINDOW_CLOSED;
			GAE_HashString_t id = 0;
			GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(int), GAE_HashString_compare);
			GAE_Event_t* event = 0;

			id = GAE_HASH_WINDOW;
			GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->window.windowID));
			event = GAE_Event_create(type, params);

			GAE_EventSystem_sendEvent(system, event);
			GAE_Event_delete(event);
		}
		break;
		default:
		break;
	}
}

void handleTextEditingEvent(SDL_Event* sdlEvent, GAE_EventSystem_t* system) {
	GAE_UNUSED(sdlEvent);
	GAE_UNUSED(system);
}

void handleTextInputEvent(SDL_Event* sdlEvent, GAE_EventSystem_t* system) {
	GAE_UNUSED(sdlEvent);
	GAE_UNUSED(system);
}

void handleQuitEvent(SDL_Event* sdlEvent, GAE_EventSystem_t* system) {
	GAE_UNUSED(sdlEvent);
	sendSimpleEvent(GAE_EVENT_APP_DESTROYED, system);
}

void handleUserEvent(SDL_Event* sdlEvent, GAE_EventSystem_t* system) {
	GAE_HashString_t type = GAE_EVENT_USER_EVENT;
	GAE_HashString_t id = 0;
	GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(void*), GAE_HashString_compare);
	GAE_Event_t* event = 0;

	id = GAE_HASH_TYPE;
	GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->user.type));
	id = GAE_HASH_WINDOW;
	GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->user.windowID));
	id = GAE_HASH_CODE;
	GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->user.code));
	id = GAE_HASH_DATA1;
	GAE_Map_push(params, (void*)&id, sdlEvent->user.data1);
	id = GAE_HASH_DATA2;
	GAE_Map_push(params, (void*)&id, sdlEvent->user.data2);
	event = GAE_Event_create(type, params);

	GAE_EventSystem_sendEvent(system, event);
	GAE_Event_delete(event);
}

void handleSysWMEvent(SDL_Event* sdlEvent, GAE_EventSystem_t* system) {
	GAE_UNUSED(sdlEvent);
	GAE_UNUSED(system);
}

void handleDropEvent(SDL_Event* sdlEvent, GAE_EventSystem_t* system) {
	GAE_HashString_t type = GAE_EVENT_FILE_DROPPED;
	GAE_HashString_t id = 0;
	GAE_Map_t* params = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(char*), GAE_HashString_compare);
	GAE_Event_t* event = 0;

	id = GAE_HASH_FILE;
	GAE_Map_push(params, (void*)&id, (void*)(&sdlEvent->drop.file));
	event = GAE_Event_create(type, params);

	GAE_EventSystem_sendEvent(system, event);
	SDL_free(sdlEvent->drop.file);
	GAE_Event_delete(event);
}

void handleAppEvent(SDL_Event* sdlEvent, GAE_EventSystem_t* system) {
	GAE_UNUSED(sdlEvent);
	GAE_UNUSED(system);
}
