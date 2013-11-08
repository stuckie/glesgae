#include "LinuxInputSystem.h"

#include "../Controller.h"
#include "../../Events/EventSystem.h"
#include "../../Events/Event.h"
#include "../../Utils/List.h"
#include "../../Utils/Map.h"
#include "../../Utils/Array.h"

#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>

static GAE_EventType_t Keyboard_KeyDown = 0;
static GAE_EventType_t Keyboard_KeyUp = 0;

static GAE_EventType_t Mouse_ButtonUp = 0;
static GAE_EventType_t Mouse_ButtonDown = 0;
static GAE_EventType_t Mouse_Moved = 0;

GAE_KeyType_t convertKey(KeySym x11Key);

GAE_InputSystem_t* GAE_InputSystem_create(GAE_EventSystem_t* eventSystem) {
	GAE_InputSystem_t* system = malloc(sizeof(GAE_InputSystem_t));

	if (0 == Keyboard_KeyDown)
		Keyboard_KeyDown = GAE_HashString_create("Input::Key::Press");
	if (0 == Keyboard_KeyUp)
		Keyboard_KeyUp = GAE_HashString_create("Input::Key::Release");
	if (0 == Mouse_ButtonUp)
		Mouse_ButtonUp = GAE_HashString_create("Input::Mouse::ButtonRelease");
	if (0 == Mouse_ButtonDown)
		Mouse_ButtonDown = GAE_HashString_create("Input::Mouse::ButtonPress");
	if (0 == Mouse_Moved)
		Mouse_Moved = GAE_HashString_create("Input::Mouse::Moved");

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

	if (event->type == Keyboard_KeyDown) {
		GAE_HashString_t id = GAE_HashString_create("key");
		system->keyboard->keys[convertKey(*(GAE_KeyType_t*)GAE_Map_get(event->params, (void*)&id))] = GAE_TRUE;
	}
	else if (event->type == Keyboard_KeyUp) {
		GAE_HashString_t id = GAE_HashString_create("key");
		system->keyboard->keys[convertKey(*(GAE_KeyType_t*)GAE_Map_get(event->params, (void*)&id))] = GAE_FALSE;
	}
	else if (event->type == Mouse_Moved) {
		float* axis = GAE_Array_get(system->pointer->axes, 0);
		GAE_HashString_t id = GAE_HashString_create("x");
		*axis = *((float*)GAE_Map_get(event->params, (void*)&id));

		axis = GAE_Array_get(system->pointer->axes, 1);
		id = GAE_HashString_create("y");
		*axis = *((float*)GAE_Map_get(event->params, (void*)&id));
	}
	else if (event->type == Mouse_ButtonDown) {
		GAE_HashString_t id = GAE_HashString_create("button");
		unsigned int index = *((unsigned int*)GAE_Map_get(event->params, (void*)&id));
		float* button = (float*)GAE_Array_get(system->pointer->buttons, index);
		*button = 1.0F;
	}
	else if (event->type == Mouse_ButtonUp) {
		GAE_HashString_t id = GAE_HashString_create("button");
		unsigned int index = *((unsigned int*)GAE_Map_get(event->params, (void*)&id));
		float* button = (float*)GAE_Array_get(system->pointer->buttons, index);
		*button = 0.0F;
	}
	else {
		/*printf("Unknown: %d\n", event->type);*/
	}
}

GAE_InputSystem_t* GAE_InputSystem_newKeyboard(GAE_InputSystem_t* system) {
	if (0 == system->keyboard) {
		system->keyboard = GAE_Keyboard_create();
		GAE_EventSystem_registerObserver(system->eventSystem, Keyboard_KeyUp, GAE_InputSystem_getEvent, (void*)system);
		GAE_EventSystem_registerObserver(system->eventSystem, Keyboard_KeyDown, GAE_InputSystem_getEvent, (void*)system);
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
		GAE_EventSystem_registerObserver(system->eventSystem, Mouse_ButtonDown, GAE_InputSystem_getEvent, (void*)system);
		GAE_EventSystem_registerObserver(system->eventSystem, Mouse_ButtonUp, GAE_InputSystem_getEvent, (void*)system);
		GAE_EventSystem_registerObserver(system->eventSystem, Mouse_Moved, GAE_InputSystem_getEvent, (void*)system);
	}

	return system;
}

GAE_InputSystem_t* GAE_InputSystem_removeKeyboard(GAE_InputSystem_t* system, GAE_Keyboard_t* const keyboard) {
	if (system->keyboard == keyboard) {
		GAE_EventSystem_deregisterObserver(system->eventSystem, Keyboard_KeyUp, GAE_InputSystem_getEvent);
		GAE_EventSystem_deregisterObserver(system->eventSystem, Keyboard_KeyDown, GAE_InputSystem_getEvent);

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
		GAE_EventSystem_deregisterObserver(system->eventSystem, Mouse_ButtonDown, GAE_InputSystem_getEvent);
		GAE_EventSystem_deregisterObserver(system->eventSystem, Mouse_ButtonUp, GAE_InputSystem_getEvent);
		GAE_EventSystem_deregisterObserver(system->eventSystem, Mouse_Moved, GAE_InputSystem_getEvent);
		
		GAE_Pointer_delete(system->pointer);
		system->pointer = 0;
	}

	return system;
}

GAE_InputSystem_t* GAE_InputSystem_update(GAE_InputSystem_t* system) {
	return system;
}

GAE_KeyType_t convertKey(KeySym x11Key) {
	/* What an arse... */
	switch (x11Key) {
		case XK_q: case XK_Q:	return GAE_KEY_Q;
		case XK_w: case XK_W:	return GAE_KEY_W;
		case XK_e: case XK_E:	return GAE_KEY_E;
		case XK_r: case XK_R:	return GAE_KEY_R;
		case XK_t: case XK_T:	return GAE_KEY_T;
		case XK_y: case XK_Y:	return GAE_KEY_Y;
		case XK_u: case XK_U:	return GAE_KEY_U;
		case XK_i: case XK_I:	return GAE_KEY_I;
		case XK_o: case XK_O:	return GAE_KEY_O;
		case XK_p: case XK_P:	return GAE_KEY_P;
		case XK_bracketleft:	return GAE_KEY_LEFT_SQUARE_BRACKET;
		case XK_bracketright:	return GAE_KEY_RIGHT_SQUARE_BRACKET;
		case XK_a: case XK_A:	return GAE_KEY_A;
		case XK_s: case XK_S:	return GAE_KEY_S;
		case XK_d: case XK_D:	return GAE_KEY_D;
		case XK_f: case XK_F:	return GAE_KEY_F;
		case XK_g: case XK_G:	return GAE_KEY_G;
		case XK_h: case XK_H:	return GAE_KEY_H;
		case XK_j: case XK_J:	return GAE_KEY_J;
		case XK_k: case XK_K:	return GAE_KEY_K;
		case XK_l: case XK_L:	return GAE_KEY_L;
		case XK_semicolon:		return GAE_KEY_SEMICOLON;
		case XK_quotedbl:		return GAE_KEY_APOSTROPHE;
		case XK_numbersign:		return GAE_KEY_TILDE;
		case XK_slash:			return GAE_KEY_FORWARDSLASH;
		case XK_z: case XK_Z:	return GAE_KEY_Z;
		case XK_x: case XK_X:	return GAE_KEY_X;
		case XK_c: case XK_C:	return GAE_KEY_C;
		case XK_v: case XK_V:	return GAE_KEY_V;
		case XK_b: case XK_B:	return GAE_KEY_B;
		case XK_n: case XK_N:	return GAE_KEY_N;
		case XK_m: case XK_M:	return GAE_KEY_M;
		case XK_comma:			return GAE_KEY_COMMA;
		case XK_period:			return GAE_KEY_PERIOD;
		case XK_backslash:		return GAE_KEY_BACKSLASH;
		case XK_space:			return GAE_KEY_SPACE;
		case XK_Return:			return GAE_KEY_RETURN;
		case XK_Left:			return GAE_KEY_ARROW_LEFT;
		case XK_Right:			return GAE_KEY_ARROW_RIGHT;
		case XK_Up:				return GAE_KEY_ARROW_UP;
		case XK_Down:			return GAE_KEY_ARROW_DOWN;
		case XK_Escape:			return GAE_KEY_ESCAPE;
		default:
			return GAE_KEY_SPACE;
	}
}
