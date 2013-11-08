#ifndef _SDL2_RENDER_WINDOW_H_
#define _SDL2_RENDER_WINDOW_H_

#include "../RenderWindow.h"

struct SDL_Window;

typedef struct GAE_SDL2_RenderWindow_s {
	struct SDL_Window* window;
	unsigned int flags;
} GAE_SDL2_RenderWindow_t;

#endif
