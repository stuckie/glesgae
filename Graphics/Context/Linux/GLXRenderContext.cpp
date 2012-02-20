#include "GLXRenderContext.h"
#include "../../Window/X11/X11RenderWindow.h"
#include "../../Target/Screen/ScreenRenderTarget.h"
#include "../../Target/Buffer/BufferRenderTarget.h"
#include "../../Target/Texture/TextureRenderTarget.h"
#include "../../State/GLES1/GLES1State.h"
#include "../../../Utils/Logger.h"

#include <cstdlib>

using namespace GLESGAE;

GLXRenderContext::GLXRenderContext()
: RenderContext()
, mWindow()
, mRenderState(new GLES1State)
, mRenderer()
, mContext()
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
	
	// Grab us a double buffered display, with RGBA colour specs and whatever the Window wants for BPP.
	int visualArgs[]  = {
		GLX_RGBA
	,	GLX_DEPTH_SIZE, mWindow->getBPP()
	,	GLX_DOUBLEBUFFER
	,	None
	};
	
	XVisualInfo* visualInfo(glXChooseVisual(mWindow->getDisplay(), XDefaultScreen(mWindow->getDisplay()), visualArgs));
	if (0 == visualInfo) {
		// Again, need to handle this...
	}
	
	// Create the context with no sharing of display lists, and DRI if possible.
	mContext = glXCreateContext(mWindow->getDisplay(), visualInfo, 0, true);
	if (0 == mContext) {
		// More death...
	}
	
	// Cleanup X junk
	free(visualInfo);
	
	// Bind the context
	glXMakeCurrent(mWindow->getDisplay(), mWindow->getWindow(), mContext);
	
	// Ensure that the viewport matches the dimensions of the window.
	glViewport(0, 0, mWindow->getWidth(), mWindow->getHeight());
	glScissor(0, 0, mWindow->getWidth(), mWindow->getHeight());
	
	// Set a clear colour
	glClearColor(0.4F, 0.4F, 0.4F, 0.0F);
	
	// May as well do the first clear here.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLXRenderContext::shutdown()
{
	// Destroy the Context.. we should be fine here as the Context should die before the Window
	glXDestroyContext(mWindow->getDisplay(), mContext);
	mContext = 0;
	glXMakeCurrent(mWindow->getDisplay(), 0, 0);
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

void GLXRenderContext::drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform)
{
	if (mRenderer != 0)
		mRenderer->drawMesh(mesh, transform);
}

Resource<RenderTarget> GLXRenderContext::createRenderTarget(const RenderTarget::Type type, const RenderTarget::Options options)
{
	switch (type) {
		case RenderTarget::TARGET_SCREEN:
			return Resource<RenderTarget>(new ScreenRenderTarget);
		break;
		case RenderTarget::TARGET_BUFFER:
			return Resource<RenderTarget>(new BufferRenderTarget(options));
		break;
		case RenderTarget::TARGET_TEXTURE:
			return Resource<RenderTarget>(new TextureRenderTarget(options));
		break;
		default:
		break;
	}
	
	return Resource<RenderTarget>();
}

Resource<RenderState> GLXRenderContext::getRenderState()
{
	return mRenderState;
}

void GLXRenderContext::setRenderState(const Resource<RenderState>& state)
{
	mRenderState = state;
}

void GLXRenderContext::setRenderer(const Resource<Renderer>& renderer)
{
	mRenderer = renderer;
}

void GLXRenderContext::bindToWindow(const Resource<RenderWindow>& window)
{
	// Rememeber the Window we're bound to
	mWindow = window.recast<X11RenderWindow>();
}

