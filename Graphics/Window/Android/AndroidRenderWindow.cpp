#include "AndroidRenderWindow.h"
#include "../../../Platform/Application.h"
#include "../../../Platform/Platform.h"

#include <cassert>

using namespace GLESGAE;

AndroidRenderWindow::AndroidRenderWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen)
: RenderWindow(name, width, height, bpp, fullscreen)
{
}

void AndroidRenderWindow::open()
{

}

AndroidRenderWindow::~AndroidRenderWindow()
{
}

void AndroidRenderWindow::close()
{
}

ANativeWindow* AndroidRenderWindow::getWindow() const
{
	Platform* platform(Application::getInstance()->getPlatform());
	return platform->getApp()->window;
}
