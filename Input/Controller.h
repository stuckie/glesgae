#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "../GAE_Types.h"

typedef unsigned int GAE_KeyType_t;

extern const GAE_KeyType_t GAE_KEY_A;
extern const GAE_KeyType_t GAE_KEY_B;
extern const GAE_KeyType_t GAE_KEY_C;
extern const GAE_KeyType_t GAE_KEY_D;
extern const GAE_KeyType_t GAE_KEY_E;
extern const GAE_KeyType_t GAE_KEY_F;
extern const GAE_KeyType_t GAE_KEY_G;
extern const GAE_KeyType_t GAE_KEY_H;
extern const GAE_KeyType_t GAE_KEY_I;
extern const GAE_KeyType_t GAE_KEY_J;
extern const GAE_KeyType_t GAE_KEY_K;
extern const GAE_KeyType_t GAE_KEY_L;
extern const GAE_KeyType_t GAE_KEY_M;
extern const GAE_KeyType_t GAE_KEY_N;
extern const GAE_KeyType_t GAE_KEY_O;
extern const GAE_KeyType_t GAE_KEY_P;
extern const GAE_KeyType_t GAE_KEY_Q;
extern const GAE_KeyType_t GAE_KEY_R;
extern const GAE_KeyType_t GAE_KEY_S;
extern const GAE_KeyType_t GAE_KEY_T;
extern const GAE_KeyType_t GAE_KEY_U;
extern const GAE_KeyType_t GAE_KEY_V;
extern const GAE_KeyType_t GAE_KEY_W;
extern const GAE_KeyType_t GAE_KEY_X;
extern const GAE_KeyType_t GAE_KEY_Y;
extern const GAE_KeyType_t GAE_KEY_Z;

extern const GAE_KeyType_t GAE_KEY_0;
extern const GAE_KeyType_t GAE_KEY_1;
extern const GAE_KeyType_t GAE_KEY_2;
extern const GAE_KeyType_t GAE_KEY_3;
extern const GAE_KeyType_t GAE_KEY_4;
extern const GAE_KeyType_t GAE_KEY_5;
extern const GAE_KeyType_t GAE_KEY_6;
extern const GAE_KeyType_t GAE_KEY_7;
extern const GAE_KeyType_t GAE_KEY_8;
extern const GAE_KeyType_t GAE_KEY_9;

extern const GAE_KeyType_t GAE_KEY_F1;
extern const GAE_KeyType_t GAE_KEY_F2;
extern const GAE_KeyType_t GAE_KEY_F3;
extern const GAE_KeyType_t GAE_KEY_F4;
extern const GAE_KeyType_t GAE_KEY_F5;
extern const GAE_KeyType_t GAE_KEY_F6;
extern const GAE_KeyType_t GAE_KEY_F7;
extern const GAE_KeyType_t GAE_KEY_F8;
extern const GAE_KeyType_t GAE_KEY_F9;
extern const GAE_KeyType_t GAE_KEY_F10;
extern const GAE_KeyType_t GAE_KEY_F11;
extern const GAE_KeyType_t GAE_KEY_F12;

extern const GAE_KeyType_t GAE_KEY_LEFT_SHIFT;
extern const GAE_KeyType_t GAE_KEY_RIGHT_SHIFT;

extern const GAE_KeyType_t GAE_KEY_LEFT_CTRL;
extern const GAE_KeyType_t GAE_KEY_RIGHT_CTRL;

extern const GAE_KeyType_t GAE_KEY_LEFT_ALT;
extern const GAE_KeyType_t GAE_KEY_RIGHT_ALT;

extern const GAE_KeyType_t GAE_KEY_CAPS_LOCK;
extern const GAE_KeyType_t GAE_KEY_RETURN;
extern const GAE_KeyType_t GAE_KEY_TAB;
extern const GAE_KeyType_t GAE_KEY_BACKSPACE;
extern const GAE_KeyType_t GAE_KEY_ESCAPE;
extern const GAE_KeyType_t GAE_KEY_SPACE;

extern const GAE_KeyType_t GAE_KEY_BACKSLASH;
extern const GAE_KeyType_t GAE_KEY_FORWARDSLASH;
extern const GAE_KeyType_t GAE_KEY_COMMA;
extern const GAE_KeyType_t GAE_KEY_PERIOD;
extern const GAE_KeyType_t GAE_KEY_SEMICOLON;
extern const GAE_KeyType_t GAE_KEY_APOSTROPHE;
extern const GAE_KeyType_t GAE_KEY_LEFT_SQUARE_BRACKET;
extern const GAE_KeyType_t GAE_KEY_RIGHT_SQUARE_BRACKET;
extern const GAE_KeyType_t GAE_KEY_BACKTICK;
extern const GAE_KeyType_t GAE_KEY_MINUS;
extern const GAE_KeyType_t GAE_KEY_PLUS;
extern const GAE_KeyType_t GAE_KEY_TILDE;
extern const GAE_KeyType_t GAE_KEY_ASTERISK;

extern const GAE_KeyType_t GAE_KEY_ARROW_UP;
extern const GAE_KeyType_t GAE_KEY_ARROW_DOWN;
extern const GAE_KeyType_t GAE_KEY_ARROW_LEFT;
extern const GAE_KeyType_t GAE_KEY_ARROW_RIGHT;

#define GAE_MAX_KEYS 77U

struct GAE_Array_s;

typedef struct GAE_Keyboard_s {
	GAE_BOOL keys[GAE_MAX_KEYS];
} GAE_Keyboard_t;

GAE_Keyboard_t* GAE_Keyboard_create(void);
void GAE_Keyboard_delete(GAE_Keyboard_t* keyboard);

typedef struct GAE_Joystick_s {
	struct GAE_Array_s* axes;
	struct GAE_Array_s* buttons;
} GAE_Joystick_t;

GAE_Joystick_t* GAE_Joystick_create(const unsigned int axes, const unsigned int buttons);
void GAE_Joystick_delete(GAE_Joystick_t* joystick);

typedef struct GAE_Pad_s {
	struct GAE_Array_s* buttons;
} GAE_Pad_t;

GAE_Pad_t* GAE_Pad_create(const unsigned int buttons);
void GAE_Pad_delete(GAE_Pad_t* pad);

typedef struct GAE_Pointer_s {
	struct GAE_Array_s* axes;
	struct GAE_Array_s* buttons;
} GAE_Pointer_t;

GAE_Pointer_t* GAE_Pointer_create(const unsigned int axes, const unsigned int buttons);
void GAE_Pointer_delete(GAE_Pointer_t* pointer);

#endif
