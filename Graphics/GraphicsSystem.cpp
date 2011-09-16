#include "GraphicsSystem.h"

#if defined(LINUX)
	#include "Window/X11RenderWindow.h"
#endif

#if defined(GLX)
	#include "Context/GLXRenderContext.h"
#elif defined(GLES1)
	#include "Context/GLES1RenderContext.h"
#elif defined(GLES2)
	#include "Context/GLES2RenderContext.h"
#endif

using namespace GLESGAE;

GraphicsSystem::GraphicsSystem(const RenderType renderType)
: mRenderType(renderType)
, mRenderContext(0)
, mWindow(0)
{
}

GraphicsSystem::~GraphicsSystem()
{
	shutdown();
}

bool GraphicsSystem::initialise(const std::string& windowName, const unsigned int width, const unsigned int height, const unsigned int, const bool)
{
	#if defined(LINUX)
		mWindow = new X11RenderWindow;
	#endif

	if ((0 == mWindow)
	|| (0 == mRenderContext)) {
		shutdown();
		return false;
	}

	mRenderContext->bindToWindow(mWindow);
	mWindow->open(windowName.c_str(), width, height);
	mRenderContext->initialise();
	mWindow->refresh();

	return true;
}

void GraphicsSystem::beginFrame()
{
}

void GraphicsSystem::setCamera(const Resource<Camera>& camera)
{
	mRenderContext->setCamera(camera);
}

void GraphicsSystem::setTextureMatrix(const Resource<Matrix4>& matrix)
{
	mRenderContext->setTextureMatrix(matrix);
}

void GraphicsSystem::drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform)
{
	mRenderContext->drawMesh(mesh, transform);
}

void GraphicsSystem::endFrame()
{
	mRenderContext->refresh();
}

void GraphicsSystem::shutdown()
{
	if (0 != mRenderContext) {
		//! TODO: Oh dear! we haven't cleared the context.. this is probably going to leak now...
		delete mRenderContext;
		mRenderContext = 0;
	}

	if (0 != mWindow) {
		delete mWindow;
		mWindow = 0;
	}
}

void GraphicsSystem::enableAlphaBlending()
{
	mRenderContext->enableAlphaBlending();
}

void GraphicsSystem::disableAlphaBlending()
{
	mRenderContext->disableAlphaBlending();
}
