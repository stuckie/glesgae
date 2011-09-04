#if defined(GLES2)

#include <cstdio>

#include "GLES2RenderContext.h"
#include "../Window/X11RenderWindow.h"

#if defined(PANDORA)
	#include <GLES2/gl2.h>
#endif

using namespace GLESGAE;

GLES2RenderContext::GLES2RenderContext()
: RenderContext()
, ShaderBasedContext()
, mWindow(0)
, mDisplay(0)
, mContext(0)
, mSurface(0)
{

}

GLES2RenderContext::~GLES2RenderContext()
{
	shutdown();
}

void GLES2RenderContext::initialise()
{
	// Get the EGL Display..
	mDisplay = eglGetDisplay( (reinterpret_cast<EGLNativeDisplayType>(mWindow->getDisplay())) );
	if (EGL_NO_DISPLAY == mDisplay) {
		printf("failed to get egl display..\n");
	}

	// Initialise the EGL Display
	if (0 == eglInitialize(mDisplay, NULL, NULL)) {
		printf("failed to init egl..\n");
	}

	// Now we want to find an EGL Surface that will work for us...
	EGLint eglAttribs[] = {
		EGL_BUFFER_SIZE, 16			// 16bit Colour Buffer
	,	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT	// We want an ES2 config
	,	EGL_NONE
	};

	EGLConfig  eglConfig;
	EGLint     numConfig;
	if (0 == eglChooseConfig(mDisplay, eglAttribs, &eglConfig, 1, &numConfig)) {
		printf("failed to get context..\n");
	}

	// Create the actual surface based upon the list of configs we've just gotten...
	mSurface = eglCreateWindowSurface(mDisplay, eglConfig, reinterpret_cast<EGLNativeWindowType>(mWindow->getWindow()), NULL);
	if (EGL_NO_SURFACE == mSurface) {
		printf("failed to get surface..\n");
	}

	// Setup the EGL context
	EGLint contextAttribs[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2
	,	EGL_NONE
	};

	// Create our Context
	mContext = eglCreateContext (mDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
	if (EGL_NO_CONTEXT == mContext) {
		printf("failed to get context...\n");
	}

	// Bind the Display, Surface and Contexts together
	eglMakeCurrent(mDisplay, mSurface, mSurface, mContext);

	// Setup the viewport
	glViewport(0, 0, mWindow->getWidth(), mWindow->getHeight());

	// Setup non-black clear colour
	glClearColor(0.4F, 0.4F, 0.4F, 1.0F);
}

void GLES2RenderContext::shutdown()
{
	eglDestroyContext(mDisplay, mContext);
	eglDestroySurface(mDisplay, mSurface);
	eglTerminate(mDisplay);
}

void GLES2RenderContext::refresh()
{
	// Trigger a buffer swap
	eglSwapBuffers(mDisplay, mSurface);

	// Clear the buffers for the next frame.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLES2RenderContext::bindToWindow(RenderWindow* const window)
{
	// Rememeber the Window we're bound to
	mWindow = reinterpret_cast<X11RenderWindow*>(window);

	// Set the context as us.
	mWindow->setContext(this);
}

#endif
