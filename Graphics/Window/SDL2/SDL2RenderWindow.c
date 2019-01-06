#include "SDL2RenderWindow.h"
#include "SDL2/SDL.h"
#include <stdlib.h>
#include <string.h>

GAE_RenderWindow_t* GAE_RenderWindow_create(char* const name, const unsigned int width, const unsigned int height, const unsigned int bpp, const GAE_BOOL fullscreen) {
	GAE_RenderWindow_t* window = (GAE_RenderWindow_t*)malloc(sizeof(GAE_RenderWindow_t));
	GAE_SDL2_RenderWindow_t* sdlWindow = (GAE_SDL2_RenderWindow_t*)malloc(sizeof(GAE_SDL2_RenderWindow_t));

	window->name = name;
	window->width = width;
	window->height = height;
	window->bpp = bpp;
	window->isFullscreen = fullscreen;

	sdlWindow->window = 0;
	sdlWindow->flags = 0;
	if (GAE_TRUE == fullscreen)
		sdlWindow->flags |= SDL_WINDOW_FULLSCREEN;

	window->platform = (void*)sdlWindow;

	return window;
}

GAE_RenderWindow_t* GAE_RenderWindow_open(GAE_RenderWindow_t* window) {
	GAE_SDL2_RenderWindow_t* sdlWindow = (GAE_SDL2_RenderWindow_t*)window->platform;

	sdlWindow->window = SDL_CreateWindow(window->name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window->width, window->height, sdlWindow->flags);
	
	return window;
}

GAE_RenderWindow_t* GAE_RenderWindow_refresh(GAE_RenderWindow_t* window) {
	return window;
}

GAE_RenderWindow_t* GAE_RenderWindow_close(GAE_RenderWindow_t* window) {
	GAE_SDL2_RenderWindow_t* sdlWindow = (GAE_SDL2_RenderWindow_t*)window->platform;
	if (0 != sdlWindow->window) {
		SDL_DestroyWindow(sdlWindow->window);
		sdlWindow->window = 0;
	}

	return window;
}

void GAE_RenderWindow_delete(GAE_RenderWindow_t* window) {
	GAE_SDL2_RenderWindow_t* sdlWindow = (GAE_SDL2_RenderWindow_t*)window->platform;
	GAE_RenderWindow_close(window);

	free(sdlWindow);
	sdlWindow = 0;

	free(window);
	window = 0;
}
