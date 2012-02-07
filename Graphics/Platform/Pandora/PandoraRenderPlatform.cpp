#include "PandoraRenderPlatform.h"

#include "../../Context/Pandora/PandoraRenderContext.h"
#include "../../Window/X11/X11RenderWindow.h"

using namespace GLESGAE;

PandoraRenderPlatform::PandoraRenderPlatform()
{
}

PandoraRenderPlatform::~PandoraRenderPlatform()
{
}

void PandoraRenderPlatform::initialise()
{
}

void PandoraRenderPlatform::refresh()
{
}

void PandoraRenderPlatform::shutdown()
{
}

Resource<RenderWindow> PandoraRenderPlatform::createWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen)
{
	return Resource<RenderWindow>(new X11RenderWindow(name, width, height, bpp, fullscreen));
}

Resource<RenderContext> PandoraRenderPlatform::createContext()
{
	return Resource<RenderContext>(new PandoraRenderContext);
}
