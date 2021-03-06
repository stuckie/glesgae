#ifndef _SDL2_EVENTS_H_
#define _SDL2_EVENTS_H_

#include "../../GAE_Types.h"

void GAE_Events_create(void);

extern GAE_HashString_t GAE_EVENT_KEYBOARD;

extern GAE_HashString_t GAE_EVENT_MOUSE_MOTION;
extern GAE_HashString_t GAE_EVENT_MOUSE_BUTTON;
extern GAE_HashString_t GAE_EVENT_MOUSE_WHEEL;

extern GAE_HashString_t GAE_EVENT_JOYSTICK_AXIS;
extern GAE_HashString_t GAE_EVENT_JOYSTICK_HAT;
extern GAE_HashString_t GAE_EVENT_JOYSTICK_BUTTON;
extern GAE_HashString_t GAE_EVENT_JOYSTICK_BALL;
extern GAE_HashString_t GAE_EVENT_JOYSTICK_DEVICE;

extern GAE_HashString_t GAE_EVENT_CONTROLLER_MOTION;
extern GAE_HashString_t GAE_EVENT_CONTROLLER_BUTTON;
extern GAE_HashString_t GAE_EVENT_CONTROLLER_DEVICE;

extern GAE_HashString_t GAE_EVENT_TOUCH;
extern GAE_HashString_t GAE_EVENT_MULTIGESTURE;
extern GAE_HashString_t GAE_EVENT_DOLLARGESTURE;

extern GAE_HashString_t GAE_EVENT_WINDOW_SHOWN;
extern GAE_HashString_t GAE_EVENT_WINDOW_HIDDEN;
extern GAE_HashString_t GAE_EVENT_WINDOW_EXPOSED;
extern GAE_HashString_t GAE_EVENT_WINDOW_MOVED;
extern GAE_HashString_t GAE_EVENT_WINDOW_RESIZED;
extern GAE_HashString_t GAE_EVENT_WINDOW_MINIMISED;
extern GAE_HashString_t GAE_EVENT_WINDOW_MAXIMISED;
extern GAE_HashString_t GAE_EVENT_WINDOW_RESTORED;
extern GAE_HashString_t GAE_EVENT_WINDOW_ENTER;
extern GAE_HashString_t GAE_EVENT_WINDOW_LEAVE;
extern GAE_HashString_t GAE_EVENT_WINDOW_CLOSED;

extern GAE_HashString_t GAE_EVENT_FOCUS_GAINED;
extern GAE_HashString_t GAE_EVENT_FOCUS_LOST;

extern GAE_HashString_t GAE_EVENT_APP_DESTROYED;

extern GAE_HashString_t GAE_EVENT_USER_EVENT;

extern GAE_HashString_t GAE_EVENT_FILE_DROPPED;

extern GAE_HashString_t GAE_HASH_EVENT;
extern GAE_HashString_t GAE_HASH_WINDOW;
extern GAE_HashString_t GAE_HASH_X;
extern GAE_HashString_t GAE_HASH_Y;
extern GAE_HashString_t GAE_HASH_WIDTH;
extern GAE_HashString_t GAE_HASH_HEIGHT;
extern GAE_HashString_t GAE_HASH_TYPE;
extern GAE_HashString_t GAE_HASH_CODE;
extern GAE_HashString_t GAE_HASH_DATA1;
extern GAE_HashString_t GAE_HASH_DATA2;
extern GAE_HashString_t GAE_HASH_FILE;

#endif
