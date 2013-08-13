#include "AndroidRenderContext.h"
#include "../../Renderer/Renderer.h"
#include "../../Window/Android/AndroidRenderWindow.h"
#include "../../Target/Screen/ScreenRenderTarget.h"
#include "../../Target/Buffer/BufferRenderTarget.h"
#include "../../Target/Texture/TextureRenderTarget.h"
#if defined(GLES1)
	#include "../../State/GLES1/GLES1State.h"
#elif defined(GLES2)
	#include "../../State/GLES2/GLES2State.h"
#endif
#include "../../../Platform/Application.h"
#include "../../../Utils/Logger.h"

#include <android_native_app_glue.h>

using namespace GLESGAE;

AndroidRenderContext::AndroidRenderContext()
: RenderContext()
, mWindow()
#if defined(GLES1)
, mRenderState(new GLES1State)
#elif defined(GLES2)
, mRenderState(new GLES2State)
#endif
, mRenderer()
, mDisplay(0)
, mContext(0)
, mSurface(0)
{
}

AndroidRenderContext::~AndroidRenderContext()
{
	shutdown();
}

void AndroidRenderContext::initialise()
{
	// Get the EGL Display..
	mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (EGL_NO_DISPLAY == mDisplay) 
		Application::getInstance()->getLogger()->log("Failed to get egl display..\n", Logger::LOG_TYPE_ERROR);

	// Initialise the EGL Display
	if (EGL_FALSE == eglInitialize(mDisplay, NULL, NULL))
		Application::getInstance()->getLogger()->log("Failed to init egl..\n", Logger::LOG_TYPE_ERROR);

	// Now we want to find an EGL Surface that will work for us...
	EGLint eglAttribs[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT
	,	EGL_BUFFER_SIZE, mWindow->getBPP()	// Colour Buffer
#if defined(GLES2)
	,	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT	// We want an ES2 config
#endif
	,	EGL_NONE
	};

	EGLConfig	eglConfig;
	EGLint		numConfig;
	EGLint		eglFormat;
	// This may cause some trouble on some Android devices, as we're only picking the first config that comes back....
	if (EGL_FALSE == eglChooseConfig(mDisplay, eglAttribs, &eglConfig, 1, &numConfig))
		Application::getInstance()->getLogger()->log("Failed to get context..\n", Logger::LOG_TYPE_ERROR);

	// Grab the visual ID so we can pass it back to Android
	eglGetConfigAttrib(mDisplay, eglConfig, EGL_NATIVE_VISUAL_ID, &eglFormat);
	
	// Tell Android to create us a Window
	ANativeWindow_setBuffersGeometry(mWindow->getWindow(), mWindow->getWidth(), mWindow->getHeight(), eglFormat);
	
	// Create the actual surface based upon the list of configs we've just gotten...
	EGLint windowAttribs[] = {
		EGL_RENDER_BUFFER,	EGL_BACK_BUFFER
	,	EGL_NONE
	};
	mSurface = eglCreateWindowSurface(mDisplay, eglConfig, mWindow->getWindow(), windowAttribs);
	if (EGL_NO_SURFACE == mSurface)
		Application::getInstance()->getLogger()->log("Failed to get surface..\n", Logger::LOG_TYPE_ERROR);

	// Setup the EGL Context
	EGLint contextAttribs[] = {
#if defined(GLES1)
		EGL_CONTEXT_CLIENT_VERSION, 1
#elif defined(GLES2)
		EGL_CONTEXT_CLIENT_VERSION, 2
#endif
	,	EGL_NONE
	};

	// Create our Context
	mContext = eglCreateContext(mDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
	if (EGL_NO_CONTEXT == mContext)
		Application::getInstance()->getLogger()->log("Failed to get context...\n", Logger::LOG_TYPE_ERROR);

	// Bind the Display, Surface and Contexts together
	eglMakeCurrent(mDisplay, mSurface, mSurface, mContext);

	// Set up our viewport
	glViewport(0, 0, mWindow->getWidth(), mWindow->getHeight());
	glScissor(0, 0, mWindow->getWidth(), mWindow->getHeight());

	// Set a non-black clear colour
	glClearColor(0.4F, 1.4F, 0.4F, 1.0F);
}

void AndroidRenderContext::shutdown()
{
	eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(mDisplay, mContext);
	eglDestroySurface(mDisplay, mSurface);
	eglTerminate(mDisplay);
}

void AndroidRenderContext::refresh()
{
	glDisable(GL_SCISSOR_TEST);
	
	// Trigger a buffer swap
	eglSwapBuffers(mDisplay, mSurface);
	
	// Clear the buffers for the next frame.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_SCISSOR_TEST);
}

void AndroidRenderContext::drawMesh(Mesh* const mesh, Matrix4* const transform)
{
	if (mRenderer != 0)
		mRenderer->drawMesh(mesh, transform);
}

RenderTarget* AndroidRenderContext::createRenderTarget(const RenderTarget::Type type, const RenderTarget::Options options)
{
	switch (type) {
		case RenderTarget::TARGET_SCREEN:
			return new ScreenRenderTarget;
		break;
		case RenderTarget::TARGET_BUFFER:
			return new BufferRenderTarget(options);
		break;
		case RenderTarget::TARGET_TEXTURE:
			return new TextureRenderTarget(options);
		break;
		default:
			return 0;
		break;
	}
}

RenderState* AndroidRenderContext::getRenderState()
{
	return mRenderState;
}

void AndroidRenderContext::setRenderer(Renderer* const renderer)
{
	mRenderer = renderer;
}

void AndroidRenderContext::bindToWindow(RenderWindow* const window)
{
	// Rememeber the Window we're bound to
	mWindow = reinterpret_cast<AndroidRenderWindow*>(window);
}

RenderWindow* AndroidRenderContext::getWindow() const
{
	return mWindow;
}
