#ifndef _SDL2_SPRITE_H_
#define _SDL2_SPRITE_H_

#include "../../../GAE_Types.h"

struct GAE_Texture_s;
struct SDL_Rect;

typedef struct GAE_Sprite_s {
	struct GAE_Texture_s* texture;
	struct SDL_Rect* srcRect;
	struct SDL_Rect* dstRect;
} GAE_Sprite_t;

GAE_Sprite_t* GAE_Sprite_create(const char* texturePath);
void GAE_Sprite_delete(GAE_Sprite_t* sprite);

#endif
