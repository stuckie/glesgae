#include "AndroidRenderPlatform.h"

#include "../../Context/Android/AndroidRenderContext.h"
#include "../../Window/Android/AndroidRenderWindow.h"

using namespace GLESGAE;

AndroidRenderPlatform::AndroidRenderPlatform()
{
}

AndroidRenderPlatform::~AndroidRenderPlatform()
{
}

void AndroidRenderPlatform::initialise()
{
}

void AndroidRenderPlatform::refresh()
{
}

void AndroidRenderPlatform::shutdown()
{
}

RenderWindow* AndroidRenderPlatform::createWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen)
{
	return new AndroidRenderWindow(name, width, height, bpp, fullscreen);
}

RenderContext* AndroidRenderPlatform::createContext()
{
	return new AndroidRenderContext;
}

