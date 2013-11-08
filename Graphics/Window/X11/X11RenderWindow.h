#ifndef _X11_RENDER_WINDOW_H_
#define _X11_RENDER_WINDOW_H_

#include "../RenderWindow.h"
#include <X11/Xlib.h>

typedef struct GAE_X11_RenderWindow_s {
	Display* display;
	Window window;
	Atom deleteMessage;
} GAE_X11_RenderWindow_t;

#endif
