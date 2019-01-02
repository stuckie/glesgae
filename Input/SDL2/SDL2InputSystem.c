#include "SDL2InputSystem.h"

#include "../Controller.h"
#include "../../Events/SDL2/SDL2Events.h"
#include "../../Events/EventSystem.h"
#include "../../Events/Event.h"
#include "../../Utils/List.h"
#include "../../Utils/Map.h"
#include "../../Utils/Array.h"

#include <stdlib.h>
#include "SDL2/SDL.h"

GAE_KeyType_t convertKey(SDL_Keycode key);

GAE_InputSystem_t* GAE_InputSystem_create(GAE_EventSystem_t* eventSystem) {
	GAE_InputSystem_t* system = (GAE_InputSystem_t*)malloc(sizeof(GAE_InputSystem_t));

	system->eventSystem = eventSystem;
	system->keyboard = 0;
	system->pointer = 0;
	system->joysticks = GAE_SingleList_create(sizeof(GAE_Joystick_t));
	system->pads = GAE_SingleList_create(sizeof(GAE_Pad_t));

	return system;
}

void GAE_InputSystem_delete(GAE_InputSystem_t* system) {
	if (0 != system->keyboard)
		GAE_InputSystem_removeKeyboard(system, system->keyboard);
	if (0 != system->pointer)
		GAE_InputSystem_removePointer(system, system->pointer);
	GAE_SingleList_delete(system->joysticks);
	GAE_SingleList_delete(system->pads);

	free(system);
	system = 0;
}

void GAE_InputSystem_getEvent(GAE_Event_t* const event, void* userData) {
	GAE_InputSystem_t* system = (GAE_InputSystem_t*)userData;
	SDL_Event* sdlEvent = (SDL_Event*)GAE_Map_begin(event->params);

	if (GAE_EVENT_KEYBOARD == event->type) {
		switch (sdlEvent->type) {
			case SDL_KEYUP:
				system->keyboard->keys[convertKey(sdlEvent->key.keysym.sym)] = GAE_FALSE;
			break;
			case SDL_KEYDOWN:
				system->keyboard->keys[convertKey(sdlEvent->key.keysym.sym)] = GAE_TRUE;
			break;
			default:
			break;
		}
	}

	if (GAE_EVENT_MOUSE_MOTION == event->type) {
		switch (sdlEvent->type) {
			case SDL_MOUSEMOTION: {
				float* x = (float*)GAE_Array_get(system->pointer->axes, 0U);
				float* y = (float*)GAE_Array_get(system->pointer->axes, 1U);

				*x = sdlEvent->motion.x;
				*y = sdlEvent->motion.y;
			}
			break;
		}
	}
	
	if (GAE_EVENT_MOUSE_BUTTON == event->type) {
		switch (sdlEvent->type) {
			case SDL_MOUSEBUTTONDOWN: {
				float* button = (float*)GAE_Array_get(system->pointer->buttons, sdlEvent->button.which);
				
				*button = 1.0F;
			}
			break;
			case SDL_MOUSEBUTTONUP: {
				float* button = (float*)GAE_Array_get(system->pointer->buttons, sdlEvent->button.which);
				
				*button = 0.0F;
			}
			break;
		}
	}
}

GAE_InputSystem_t* GAE_InputSystem_newKeyboard(GAE_InputSystem_t* system) {
	if (0 == system->keyboard) {
		system->keyboard = GAE_Keyboard_create();
		GAE_EventSystem_registerObserver(system->eventSystem, GAE_EVENT_KEYBOARD, GAE_InputSystem_getEvent, (void*)system);
	}

	return system;
}

GAE_InputSystem_t* GAE_InputSystem_newJoystick(GAE_InputSystem_t* system) {
	return system;
}

GAE_InputSystem_t* GAE_InputSystem_newPad(GAE_InputSystem_t* system) {
	return system;
}

GAE_InputSystem_t* GAE_InputSystem_newPointer(GAE_InputSystem_t* system) {
	if (0 == system->pointer) {
		system->pointer = GAE_Pointer_create(2U, 5U);
		GAE_EventSystem_registerObserver(system->eventSystem, GAE_EVENT_MOUSE_MOTION, GAE_InputSystem_getEvent, (void*)system);
		GAE_EventSystem_registerObserver(system->eventSystem, GAE_EVENT_MOUSE_BUTTON, GAE_InputSystem_getEvent, (void*)system);
	}

	return system;
}

GAE_InputSystem_t* GAE_InputSystem_removeKeyboard(GAE_InputSystem_t* system, GAE_Keyboard_t* const keyboard) {
	if (system->keyboard == keyboard) {
		GAE_EventSystem_deregisterObserver(system->eventSystem, GAE_EVENT_KEYBOARD, GAE_InputSystem_getEvent);

		GAE_Keyboard_delete(system->keyboard);
		system->keyboard = 0;
	}

	return system;
}

GAE_InputSystem_t* GAE_InputSystem_removeJoystick(GAE_InputSystem_t* system, GAE_Joystick_t* const joystick) {
	GAE_UNUSED(joystick);

	return system;
}

GAE_InputSystem_t* GAE_InputSystem_removePad(GAE_InputSystem_t* system, GAE_Pad_t* const pad) {
	GAE_UNUSED(pad);

	return system;
}

GAE_InputSystem_t* GAE_InputSystem_removePointer(GAE_InputSystem_t* system, GAE_Pointer_t* const pointer) {
	if (system->pointer == pointer) {
		GAE_EventSystem_deregisterObserver(system->eventSystem, GAE_EVENT_MOUSE_MOTION, GAE_InputSystem_getEvent);
		GAE_EventSystem_deregisterObserver(system->eventSystem, GAE_EVENT_MOUSE_BUTTON, GAE_InputSystem_getEvent);
		
		GAE_Pointer_delete(system->pointer);
		system->pointer = 0;
	}

	return system;
}

GAE_InputSystem_t* GAE_InputSystem_update(GAE_InputSystem_t* system) {
	return system;
}

GAE_KeyType_t convertKey(SDL_Keycode key) {
	/* What an arse... */
	switch (key) {
		case SDLK_q: 			return GAE_KEY_Q;
		case SDLK_w: 			return GAE_KEY_W;
		case SDLK_e: 			return GAE_KEY_E;
		case SDLK_r: 			return GAE_KEY_R;
		case SDLK_t: 			return GAE_KEY_T;
		case SDLK_y: 			return GAE_KEY_Y;
		case SDLK_u: 			return GAE_KEY_U;
		case SDLK_i: 			return GAE_KEY_I;
		case SDLK_o: 			return GAE_KEY_O;
		case SDLK_p: 			return GAE_KEY_P;
		case SDLK_LEFTBRACKET:	return GAE_KEY_LEFT_SQUARE_BRACKET;
		case SDLK_RIGHTBRACKET:	return GAE_KEY_RIGHT_SQUARE_BRACKET;
		case SDLK_a: 			return GAE_KEY_A;
		case SDLK_s: 			return GAE_KEY_S;
		case SDLK_d: 			return GAE_KEY_D;
		case SDLK_f: 			return GAE_KEY_F;
		case SDLK_g: 			return GAE_KEY_G;
		case SDLK_h: 			return GAE_KEY_H;
		case SDLK_j: 			return GAE_KEY_J;
		case SDLK_k: 			return GAE_KEY_K;
		case SDLK_l: 			return GAE_KEY_L;
		case SDLK_SEMICOLON:	return GAE_KEY_SEMICOLON;
		case SDLK_QUOTEDBL:		return GAE_KEY_APOSTROPHE;
		case SDLK_BACKQUOTE:	return GAE_KEY_TILDE;
		case SDLK_SLASH:		return GAE_KEY_FORWARDSLASH;
		case SDLK_z: 			return GAE_KEY_Z;
		case SDLK_x: 			return GAE_KEY_X;
		case SDLK_c: 			return GAE_KEY_C;
		case SDLK_v: 			return GAE_KEY_V;
		case SDLK_b: 			return GAE_KEY_B;
		case SDLK_n: 			return GAE_KEY_N;
		case SDLK_m: 			return GAE_KEY_M;
		case SDLK_COMMA:		return GAE_KEY_COMMA;
		case SDLK_PERIOD:		return GAE_KEY_PERIOD;
		case SDLK_BACKSLASH:	return GAE_KEY_BACKSLASH;
		case SDLK_SPACE:		return GAE_KEY_SPACE;
		case SDLK_RETURN:		return GAE_KEY_RETURN;
		case SDLK_LEFT:			return GAE_KEY_ARROW_LEFT;
		case SDLK_RIGHT:		return GAE_KEY_ARROW_RIGHT;
		case SDLK_UP:			return GAE_KEY_ARROW_UP;
		case SDLK_DOWN:			return GAE_KEY_ARROW_DOWN;
		case SDLK_ESCAPE:		return GAE_KEY_ESCAPE;
		default:
			return GAE_KEY_SPACE;
	}
}
