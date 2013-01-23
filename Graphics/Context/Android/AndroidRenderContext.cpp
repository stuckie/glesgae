#include "AndroidRenderContext.h"
#include "../../Window/Android/AndroidRenderWindow.h"
#include "../../Target/Screen/ScreenRenderTarget.h"
#include "../../Target/Buffer/BufferRenderTarget.h"
#if defined(GLES1)
	#include "../../State/GLES1/GLES1State.h"
#elif defined(GLES2)
	#include "../../State/GLES2/GLES2State.h"
#endif
#include "../../../Platform/Application.h"

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
	mDisplay = eglGetDisplay( (reinterpret_cast<EGLNativeDisplayType>(mWindow->getDisplay())) );
	if (EGL_NO_DISPLAY == mDisplay) 
		Application::getInstance()->getLogger()->log("Failed to get egl display..\n", Logger::LOG_TYPE_ERROR);

	// Initialise the EGL Display
	if (0 == eglInitialize(mDisplay, NULL, NULL))
		Application::getInstance()->getLogger()->log("Failed to init egl..\n", Logger::LOG_TYPE_ERROR);

	// Now we want to find an EGL Surface that will work for us...
	EGLint eglAttribs[] = {
		EGL_BUFFER_SIZE, 16	// 16bit Colour Buffer
#if defined(GLES2)
	,	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT	// We want an ES2 config
#endif
	,	EGL_NONE
	};

	EGLConfig  eglConfig;
	EGLint     numConfig;
	if (0 == eglChooseConfig(mDisplay, eglAttribs, &eglConfig, 1, &numConfig))
		Application::getInstance()->getLogger()->log("Failed to get context..\n", Logger::LOG_TYPE_ERROR);

	// Create the actual surface based upon the list of configs we've just gotten...
	mSurface = eglCreateWindowSurface(mDisplay, eglConfig, reinterpret_cast<EGLNativeWindowType>(mWindow->getWindow()), NULL);
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
	mContext = eglCreateContext (mDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
	if (EGL_NO_CONTEXT == mContext)
		Application::getInstance()->getLogger()->log("Failed to get context...\n", Logger::LOG_TYPE_ERROR);

	// Bind the Display, Surface and Contexts together
	eglMakeCurrent(mDisplay, mSurface, mSurface, mContext);

	// Set up our viewport
	glViewport(0, 0, mWindow->getWidth(), mWindow->getHeight());

	// Set a non-black clear colour
	glClearColor(0.4F, 0.4F, 0.4F, 1.0F);
}

void AndroidRenderContext::shutdown()
{
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

void AndroidRenderContext::drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform)
{
	if (mRenderer != 0)
		mRenderer->drawMesh(mesh, transform);
}

Resource<RenderTarget> AndroidRenderContext::createRenderTarget(const RenderTarget::Type type, const RenderTarget::Options options)
{
	switch (type) {
		case RenderTarget::TARGET_SCREEN:
			return Resource<RenderTarget>(new ScreenRenderTarget);
		break;
		case RenderTarget::TARGET_BUFFER:
			return Resource<RenderTarget>(new BufferRenderTarget(options));
		break;
		case RenderTarget::TARGET_TEXTURE:
			//return Resource<RenderTarget>(new TextureRenderTarget(options));
		break;
		default:
		break;
	}
	
	return Resource<RenderTarget>();
}

Resource<RenderState> AndroidRenderContext::getRenderState()
{
	return mRenderState;
}

void AndroidRenderContext::setRenderer(const Resource<Renderer>& renderer)
{
	mRenderer = renderer;
}

void AndroidRenderContext::bindToWindow(const Resource<RenderWindow>& window)
{
	// Rememeber the Window we're bound to
	mWindow = window.recast<AndroidRenderWindow>();
}

