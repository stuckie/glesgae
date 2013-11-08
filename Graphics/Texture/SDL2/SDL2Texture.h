#ifndef _SDL2_TEXTURE_H_
#define _SDL2_TEXTURE_H_

struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct GAE_Texture_s;

typedef struct GAE_SDL2_Texture_s {
	struct SDL_Texture* texture;
	struct SDL_Renderer* renderer;
	unsigned int format;
	int access;
} GAE_SDL2_Texture_t;

struct GAE_Texture_s* GAE_Texture_createFromSurface(struct SDL_Renderer* renderer, struct SDL_Surface* surface);

#endif
