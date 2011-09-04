#if defined(LINUX)

#include "X11RenderWindow.h"
#include "../Context/RenderContext.h"

#include <X11/Xlib.h>

using namespace GLESGAE;

X11RenderWindow::X11RenderWindow()
: mDisplay(XOpenDisplay(0))
, mWindow(0)
, mDeleteMessage()
{
}

X11RenderWindow::~X11RenderWindow()
{
	if (0 != mWindow)
		close();

	XCloseDisplay(mDisplay);
}

void X11RenderWindow::open(const char* windowName, const unsigned int width, const unsigned int height)
{
	// Store the width and height.
	mWidth = width;
	mHeight = height;

	// Create the actual window and store the pointer.
	mWindow = XCreateWindow(mDisplay						// Pointer to the Display
							, XDefaultRootWindow(mDisplay)	// Parent Window
							, 0								// X of top-left corner
							, 0								// Y of top-left corner
							, width							// requested width
							, height						// requested height
							, 0								// border width
							, CopyFromParent				// window depth
							, CopyFromParent				// window class - InputOutput / InputOnly / CopyFromParent
							, CopyFromParent				// visual type
							, 0								// value mask
							, 0);							// attributes

	// Map the window to the display.
	XMapWindow(mDisplay, mWindow);

	// Set the name
	XStoreName(mDisplay, mWindow, windowName);

	// Setup input
	XSelectInput(mDisplay, mWindow, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask);

	// register interest in the delete window message
	mDeleteMessage = XInternAtom(mDisplay, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(mDisplay, mWindow, &mDeleteMessage, 1);
}

void X11RenderWindow::setContext(RenderContext* const context)
{
	mContext = context;
}

void X11RenderWindow::refresh()
{
	mContext->refresh();
}

void X11RenderWindow::close()
{
	XDestroyWindow(mDisplay, mWindow);
	mWindow = 0;
}

#endif
