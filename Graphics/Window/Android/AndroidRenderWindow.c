#include "AndroidRenderWindow.h"

GAE_RenderWindow_t* GAE_RenderWindow_create(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const GAE_BOOL fullscreen) {
	GAE_Android_RenderWindow_t* androidWindow = (GAE_Android_RenderWindow_t*)malloc(sizeof(GAE_Android_RenderWindow_t));
	GAE_RenderWindow_t* window = (GAE_RenderWindow_t*)androidWindow;

	window->name = name;
	window->width = width;
	window->height = height;
	window->bpp = bpp;
	window->isFullscreen = fullscreen;

	return window;
}

GAE_RenderWindow_t* GAE_RenderWindow_open(GAE_RenderWindow_t* window) {
	return window;
}

GAE_RenderWindow_t* GAE_RenderWindow_refresh(GAE_RenderWindow_t* window) {
	return window;
}

GAE_RenderWindow_t* GAE_RenderWindow_close(GAE_RenderWindow_t* window) {
	return window;
}

void GAE_RenderWindow_delete(GAE_RenderWindow_t* window) {
	GAE_Android_RenderWindow_t* androidWindow = (GAE_Android_RenderWindow_t*)window;
	free(androidWindow);
	window = 0;
}
