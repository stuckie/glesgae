#ifndef _RENDER_WINDOW_H_
#define _RENDER_WINDOW_H_

#include "../../GAE_Types.h"

typedef struct GAE_RenderWindow_s {
	char* name;
	unsigned int width;
	unsigned int height;
	unsigned int bpp;
	GAE_BOOL isFullscreen;
	void* platform;
} GAE_RenderWindow_t;

GAE_RenderWindow_t* GAE_RenderWindow_create(char* const name, const unsigned int width, const unsigned int height, const unsigned int bpp, const GAE_BOOL fullscreen);
GAE_RenderWindow_t* GAE_RenderWindow_open(GAE_RenderWindow_t* window);
GAE_RenderWindow_t* GAE_RenderWindow_refresh(GAE_RenderWindow_t* window);
GAE_RenderWindow_t* GAE_RenderWindow_close(GAE_RenderWindow_t* window);
void GAE_RenderWindow_delete(GAE_RenderWindow_t* window);

#if defined(SDL2)
#include "SDL2/SDL2RenderWindow.h"
#elif defined(GLX) || defined(PANDORA)
#include "X11/X11RenderWindow.h"
#elif defined(ANDROID)
#include "Android/AndroidRenderWindow.h"
#endif

#endif

