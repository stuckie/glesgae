#if defined(GLX)

#include "GLXRenderContext.h"
#include "../Window/X11RenderWindow.h"

using namespace GLESGAE;

GLXRenderContext::GLXRenderContext()
: RenderContext()
, FixedFunctionContext()
, ShaderBasedContext()
, mWindow(0)
, mContext(0)
, mShaderBased(false)
{
}

GLXRenderContext::~GLXRenderContext()
{
	shutdown();
}

void GLXRenderContext::initialise()
{
	// Check that we have a GLX extension in the first place...
	int errorBase, eventBase;
	if (0 == glXQueryExtension(mWindow->getDisplay(), &errorBase, &eventBase)) {
		// Need to handle this...
	}

	// Grab us a double buffered display, with RGBA colour specs and a 24bit Colour Buffer
	int visualArgs[]  = {
		GLX_RGBA
	,	GLX_DEPTH_SIZE, 24
	,	GLX_DOUBLEBUFFER
	,	None
	};

	XVisualInfo* visualInfo(glXChooseVisual(mWindow->getDisplay(), XDefaultScreen(mWindow->getDisplay()), visualArgs));
	if (0 == visualInfo) {
		// Again, need to handle this...
	}

	// Create the context with no sharing of display lists, and DRI if possible.
	mContext = glXCreateContext(mWindow->getDisplay(), visualInfo, NULL, GL_TRUE);
	if (0 == mContext) {
		// More death...
	}

	// Bind the context
	glXMakeCurrent(mWindow->getDisplay(), mWindow->getWindow(), mContext);

	// Ensure that the viewport matches the dimensions of the window.
	glViewport(0, 0, mWindow->getWidth(), mWindow->getHeight());

	glScissor(0, 0, mWindow->getWidth(), mWindow->getHeight());

	// Set a clear colour
	glClearColor(0.0F, 0.0F, 0.0F, 0.0F);

	// May as well do the first clear here.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLXRenderContext::shutdown()
{
	// Destroy the Context.. we should be fine here as the Context should die before the Window.
	glXDestroyContext(mWindow->getDisplay(), mContext);
}

void GLXRenderContext::refresh()
{
	glDisable(GL_SCISSOR_TEST);

	// Trigger a buffer swap
	glXSwapBuffers(mWindow->getDisplay(), mWindow->getWindow());

	// Clear the buffers for the next frame.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_SCISSOR_TEST);
}

void GLXRenderContext::bindToWindow(RenderWindow* const window)
{
	// Rememeber the Window we're bound to
	mWindow = reinterpret_cast<X11RenderWindow*>(window);

	// Set the context as us.
	mWindow->setContext(this);
}

#endif
