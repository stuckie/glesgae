#include "X11RenderWindow.h"
#include <X11/Xlib.h>
#include <stdlib.h>
#include <string.h>

void checkFullscreen(GAE_X11_RenderWindow_t* x11Window, GAE_RenderWindow_t* window);

GAE_RenderWindow_t* GAE_RenderWindow_create(char* const name, const unsigned int width, const unsigned int height, const unsigned int bpp, const GAE_BOOL fullscreen) {
	GAE_RenderWindow_t* window = malloc(sizeof(GAE_RenderWindow_t));
	GAE_X11_RenderWindow_t* x11Window = malloc(sizeof(GAE_X11_RenderWindow_t));

	window->name = name;
	window->width = width;
	window->height = height;
	window->bpp = bpp;
	window->isFullscreen = fullscreen;

	x11Window->display = XOpenDisplay(0);
	x11Window->window = 0;
	x11Window->deleteMessage = 0;

	window->platform = (void*)x11Window;

	return window;
}

GAE_RenderWindow_t* GAE_RenderWindow_open(GAE_RenderWindow_t* window) {
	GAE_X11_RenderWindow_t* x11Window = (GAE_X11_RenderWindow_t*)window->platform;

	x11Window->window = XCreateWindow(x11Window->display 	/* Pointer to the Display */
				, XDefaultRootWindow(x11Window->display)	/* Parent Window */
				, 0											/* X of top-left corner */
				, 0											/* Y of top-left corner */
				, window->width								/* requested width */
				, window->height							/* requested height */
				, 0											/* border width */
				, CopyFromParent							/* window depth */
				, CopyFromParent							/* window class - InputOutput / InputOnly / CopyFromParent */
				, CopyFromParent							/* visual type */
				, 0											/* value mask */
				, 0);										/* attributes */

	XMapWindow(x11Window->display, x11Window->window);

	XStoreName(x11Window->display, x11Window->window, window->name);

	XSelectInput(x11Window->display, x11Window->window, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask);

	x11Window->deleteMessage = XInternAtom(x11Window->display, "WM_DELETE_WINDOW", 0);
	XSetWMProtocols(x11Window->display, x11Window->window, &x11Window->deleteMessage, 1);

	checkFullscreen(x11Window, window);

	return window;
}

void checkFullscreen(GAE_X11_RenderWindow_t* x11Window, GAE_RenderWindow_t* window)	{
	if (GAE_TRUE == window->isFullscreen) {
		XWindowAttributes xwa;
		XEvent xev;

		Atom wm_state = XInternAtom(x11Window->display, "_NET_WM_STATE", False);
		Atom fullscreen = XInternAtom(x11Window->display, "_NET_WM_STATE_FULLSCREEN", False);

		memset(&xev, 0, sizeof(xev));
		xev.type = ClientMessage;
		xev.xclient.window = x11Window->window;
		xev.xclient.message_type = wm_state;
		xev.xclient.format = 32;
		xev.xclient.data.l[0] = 1;
		xev.xclient.data.l[1] = fullscreen;
		xev.xclient.data.l[2] = 0;

		XSendEvent(x11Window->display, XDefaultRootWindow(x11Window->display), False, SubstructureNotifyMask, &xev);
		
		XGetWindowAttributes(x11Window->display, XDefaultRootWindow(x11Window->display), &xwa);
		window->width = xwa.width;
		window->height = xwa.height;
	}
}

GAE_RenderWindow_t* GAE_RenderWindow_refresh(GAE_RenderWindow_t* window) {
	return window;
}

GAE_RenderWindow_t* GAE_RenderWindow_close(GAE_RenderWindow_t* window) {
	GAE_X11_RenderWindow_t* x11Window = (GAE_X11_RenderWindow_t*)window->platform;
	if (0 != x11Window->window) {
		XDestroyWindow(x11Window->display, x11Window->window);
		x11Window->window = 0;
	}

	return window;
}

void GAE_RenderWindow_delete(GAE_RenderWindow_t* window) {
	GAE_X11_RenderWindow_t* x11Window = (GAE_X11_RenderWindow_t*)window->platform;
	GAE_RenderWindow_close(window);

	if (0 != x11Window->display) {
		XCloseDisplay(x11Window->display);
		x11Window->display = 0;
	}

	free(x11Window);
	x11Window = 0;

	free(window);
	window = 0;
}
