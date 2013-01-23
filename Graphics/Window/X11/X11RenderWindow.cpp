#include "X11RenderWindow.h"
#include <X11/Xlib.h>
#include <cstdlib>
#include <cstring>

using namespace GLESGAE;

X11RenderWindow::X11RenderWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen)
: RenderWindow(name, width, height, bpp, fullscreen)
, mDisplay(XOpenDisplay(0))
, mWindow(0)
, mDeleteMessage()
{
}

void X11RenderWindow::open()
{
	// Create the actual window and store the pointer.
	mWindow = XCreateWindow(mDisplay						// Pointer to the Display
				, XDefaultRootWindow(mDisplay)				// Parent Window
				, 0							// X of top-left corner
				, 0							// Y of top-left corner
				, mWidth						// requested width
				, mHeight						// requested height
				, 0							// border width
				, CopyFromParent					// window depth
				, CopyFromParent					// window class - InputOutput / InputOnly / CopyFromParent
				, CopyFromParent					// visual type
				, 0							// value mask
				, 0);							// attributes

	// Map the window to the display.
	XMapWindow(mDisplay, mWindow);

	// Set the name
	XStoreName(mDisplay, mWindow, mName);

	// Setup input
	XSelectInput(mDisplay, mWindow, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask);

	// register interest in the delete window message
	mDeleteMessage = XInternAtom(mDisplay, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(mDisplay, mWindow, &mDeleteMessage, 1);
	
	if (true == mFullscreen) {
		XEvent xev;
		Atom wm_state = XInternAtom(mDisplay, "_NET_WM_STATE", False);
		Atom fullscreen = XInternAtom(mDisplay, "_NET_WM_STATE_FULLSCREEN", False);

		memset(&xev, 0, sizeof(xev));
		xev.type = ClientMessage;
		xev.xclient.window = mWindow;
		xev.xclient.message_type = wm_state;
		xev.xclient.format = 32;
		xev.xclient.data.l[0] = 1;
		xev.xclient.data.l[1] = fullscreen;
		xev.xclient.data.l[2] = 0;

		XSendEvent(mDisplay, XDefaultRootWindow(mDisplay), False, SubstructureNotifyMask, &xev);
		
		XWindowAttributes xwa;
		XGetWindowAttributes(mDisplay, XDefaultRootWindow(mDisplay), &xwa);
		mWidth = xwa.width;
		mHeight = xwa.height;
	}
}

X11RenderWindow::~X11RenderWindow()
{
	if (0 != mWindow)
		close();
	
	if (0 != mDisplay)
		XCloseDisplay(mDisplay);
	
	mDisplay = 0;
}

void X11RenderWindow::close()
{
	XDestroyWindow(mDisplay, mWindow);
	mWindow = 0;
}

