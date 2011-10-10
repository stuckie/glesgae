#include "LinuxRenderPlatform.h"

#include "../../Context/Linux/GLXRenderContext.h"
#include "../../Window/X11/X11RenderWindow.h"

using namespace GLESGAE;

LinuxRenderPlatform::LinuxRenderPlatform()
{
}

LinuxRenderPlatform::~LinuxRenderPlatform()
{
}

void LinuxRenderPlatform::initialise()
{
}

void LinuxRenderPlatform::refresh()
{
}

void LinuxRenderPlatform::shutdown()
{
}

Resource<RenderWindow> LinuxRenderPlatform::createWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen)
{
	return Resource<RenderWindow>(new X11RenderWindow(name, width, height, bpp, fullscreen));
}

Resource<RenderContext> LinuxRenderPlatform::createContext()
{
	return Resource<RenderContext>(new GLXRenderContext);
}
