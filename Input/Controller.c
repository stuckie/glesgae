#include "Controller.h"

#include <string.h>
#include <stdlib.h>
#include "../Utils/Array.h"

const GAE_KeyType_t GAE_KEY_A 						= 0U;
const GAE_KeyType_t GAE_KEY_B 						= 1U;
const GAE_KeyType_t GAE_KEY_C 						= 2U;
const GAE_KeyType_t GAE_KEY_D 						= 3U;
const GAE_KeyType_t GAE_KEY_E 						= 4U;
const GAE_KeyType_t GAE_KEY_F 						= 5U;
const GAE_KeyType_t GAE_KEY_G 						= 6U;
const GAE_KeyType_t GAE_KEY_H 						= 7U;
const GAE_KeyType_t GAE_KEY_I 						= 8U;
const GAE_KeyType_t GAE_KEY_J 						= 9U;
const GAE_KeyType_t GAE_KEY_K 						= 10U;
const GAE_KeyType_t GAE_KEY_L 						= 11U;
const GAE_KeyType_t GAE_KEY_M 						= 12U;
const GAE_KeyType_t GAE_KEY_N 						= 13U;
const GAE_KeyType_t GAE_KEY_O 						= 14U;
const GAE_KeyType_t GAE_KEY_P 						= 15U;
const GAE_KeyType_t GAE_KEY_Q 						= 16U;
const GAE_KeyType_t GAE_KEY_R 						= 17U;
const GAE_KeyType_t GAE_KEY_S 						= 18U;
const GAE_KeyType_t GAE_KEY_T 						= 19U;
const GAE_KeyType_t GAE_KEY_U 						= 20U;
const GAE_KeyType_t GAE_KEY_V 						= 21U;
const GAE_KeyType_t GAE_KEY_W 						= 22U;
const GAE_KeyType_t GAE_KEY_X 						= 23U;
const GAE_KeyType_t GAE_KEY_Y 						= 24U;
const GAE_KeyType_t GAE_KEY_Z 						= 25U;

const GAE_KeyType_t GAE_KEY_0 						= 26U;
const GAE_KeyType_t GAE_KEY_1 						= 27U;
const GAE_KeyType_t GAE_KEY_2 						= 28U;
const GAE_KeyType_t GAE_KEY_3 						= 29U;
const GAE_KeyType_t GAE_KEY_4 						= 30U;
const GAE_KeyType_t GAE_KEY_5 						= 31U;
const GAE_KeyType_t GAE_KEY_6 						= 32U;
const GAE_KeyType_t GAE_KEY_7 						= 33U;
const GAE_KeyType_t GAE_KEY_8 						= 34U;
const GAE_KeyType_t GAE_KEY_9 						= 35U;

const GAE_KeyType_t GAE_KEY_F1 						= 36U;
const GAE_KeyType_t GAE_KEY_F2 						= 37U;
const GAE_KeyType_t GAE_KEY_F3 						= 38U;
const GAE_KeyType_t GAE_KEY_F4 						= 39U;
const GAE_KeyType_t GAE_KEY_F5 						= 40U;
const GAE_KeyType_t GAE_KEY_F6 						= 41U;
const GAE_KeyType_t GAE_KEY_F7 						= 42U;
const GAE_KeyType_t GAE_KEY_F8 						= 43U;
const GAE_KeyType_t GAE_KEY_F9 						= 44U;
const GAE_KeyType_t GAE_KEY_F10 					= 45U;
const GAE_KeyType_t GAE_KEY_F11 					= 46U;
const GAE_KeyType_t GAE_KEY_F12 					= 47U;

const GAE_KeyType_t GAE_KEY_LEFT_SHIFT 				= 48U;
const GAE_KeyType_t GAE_KEY_RIGHT_SHIFT 			= 49U;

const GAE_KeyType_t GAE_KEY_LEFT_CTRL 				= 50U;
const GAE_KeyType_t GAE_KEY_RIGHT_CTRL 				= 51U;

const GAE_KeyType_t GAE_KEY_LEFT_ALT 				= 52U;
const GAE_KeyType_t GAE_KEY_RIGHT_ALT 				= 53U;

const GAE_KeyType_t GAE_KEY_CAPS_LOCK 				= 54U;
const GAE_KeyType_t GAE_KEY_RETURN 					= 55U;
const GAE_KeyType_t GAE_KEY_TAB 					= 56U;
const GAE_KeyType_t GAE_KEY_BACKSPACE 				= 57U;
const GAE_KeyType_t GAE_KEY_ESCAPE 					= 58U;
const GAE_KeyType_t GAE_KEY_SPACE 					= 59U;

const GAE_KeyType_t GAE_KEY_BACKSLASH 				= 60U;
const GAE_KeyType_t GAE_KEY_FORWARDSLASH 			= 61U;
const GAE_KeyType_t GAE_KEY_COMMA					= 62U;
const GAE_KeyType_t GAE_KEY_PERIOD					= 63U;
const GAE_KeyType_t GAE_KEY_SEMICOLON				= 64U;
const GAE_KeyType_t GAE_KEY_APOSTROPHE				= 65U;
const GAE_KeyType_t GAE_KEY_LEFT_SQUARE_BRACKET		= 66U;
const GAE_KeyType_t GAE_KEY_RIGHT_SQUARE_BRACKET	= 67U;
const GAE_KeyType_t GAE_KEY_BACKTICK				= 68U;
const GAE_KeyType_t GAE_KEY_MINUS					= 69U;
const GAE_KeyType_t GAE_KEY_PLUS					= 70U;
const GAE_KeyType_t GAE_KEY_TILDE					= 71U;
const GAE_KeyType_t GAE_KEY_ASTERISK				= 72U;

const GAE_KeyType_t GAE_KEY_ARROW_UP				= 73U;
const GAE_KeyType_t GAE_KEY_ARROW_DOWN				= 74U;
const GAE_KeyType_t GAE_KEY_ARROW_LEFT				= 75U;
const GAE_KeyType_t GAE_KEY_ARROW_RIGHT				= 76U;

GAE_Keyboard_t* GAE_Keyboard_create(void) {
	GAE_Keyboard_t* keyboard = malloc(sizeof(GAE_Keyboard_t));
	memset(keyboard->keys, 0, GAE_MAX_KEYS * sizeof(unsigned int));

	return keyboard;
}

void GAE_Keyboard_delete(GAE_Keyboard_t* keyboard) {
	free(keyboard);
	keyboard = 0;
}

GAE_Joystick_t* GAE_Joystick_create(const unsigned int axes, const unsigned int buttons) {
	GAE_Joystick_t* joystick = malloc(sizeof(GAE_Joystick_t));

	joystick->axes = GAE_Array_create(sizeof(float));
	GAE_Array_reserve(joystick->axes, axes);

	joystick->buttons = GAE_Array_create(sizeof(float));
	GAE_Array_reserve(joystick->buttons, buttons);

	return joystick;
}

void GAE_Joystick_delete(GAE_Joystick_t* joystick) {
	GAE_Array_destroy(joystick->axes);
	GAE_Array_destroy(joystick->buttons);

	free(joystick);
	joystick = 0;
}

GAE_Pad_t* GAE_Pad_create(const unsigned int buttons) {
	GAE_Pad_t* pad = malloc(sizeof(GAE_Pad_t));

	pad->buttons = GAE_Array_create(sizeof(float));
	GAE_Array_reserve(pad->buttons, buttons);

	return pad;
}

void GAE_Pad_delete(GAE_Pad_t* pad) {
	GAE_Array_destroy(pad->buttons);

	free(pad);
	pad = 0;
}

GAE_Pointer_t* GAE_Pointer_create(const unsigned int axes, const unsigned int buttons) {
	GAE_Pointer_t* pointer = malloc(sizeof(GAE_Pointer_t));
	unsigned int index = 0U;

	pointer->axes = GAE_Array_create(sizeof(float));
	for (index = 0U; index < axes; ++index) {
		float* value = malloc(sizeof(float));
		*value = 0.0F;
		GAE_Array_push(pointer->axes, value);
	}

	pointer->buttons = GAE_Array_create(sizeof(float));
	for (index = 0U; index < buttons; ++index) {
		float* value = malloc(sizeof(float));
		*value = 0.0F;
		GAE_Array_push(pointer->buttons, value);
	}

	return pointer;
}

void GAE_Pointer_delete(GAE_Pointer_t* pointer) {
	GAE_Array_destroy(pointer->axes);
	GAE_Array_destroy(pointer->buttons);

	free(pointer);
	pointer = 0;
}
