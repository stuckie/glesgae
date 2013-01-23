#include "AndroidRenderWindow.h"
#include <cstdlib>
#include <cstring>

using namespace GLESGAE;

AndroidRenderWindow::AndroidRenderWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen)
: RenderWindow(name, width, height, bpp, fullscreen)
, mDisplay(0)
, mWindow(0)
{
}

void AndroidRenderWindow::open()
{

}

AndroidRenderWindow::~AndroidRenderWindow()
{
	if (0 != mWindow)
		close();
	
	if (0 != mDisplay)
		mDisplay = 0;
}

void AndroidRenderWindow::close()
{
	mWindow = 0;
}

