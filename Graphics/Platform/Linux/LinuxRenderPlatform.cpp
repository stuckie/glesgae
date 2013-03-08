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

RenderWindow* LinuxRenderPlatform::createWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen)
{
	return new X11RenderWindow(name, width, height, bpp, fullscreen);
}

RenderContext* LinuxRenderPlatform::createContext()
{
	return new GLXRenderContext;
}
