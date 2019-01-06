#include "../../Sprite.h"

#include "../../Texture.h"
#include "../../../File/File.h"
#include "SDL2/SDL.h"

#include <stdlib.h>
#include <string.h>

GAE_Sprite_t* GAE_Sprite_create(const char* texturePath) {
	GAE_Sprite_t* sprite = (GAE_Sprite_t*)malloc(sizeof(GAE_Sprite_t));

	GAE_File_t* textureFile = GAE_File_create(texturePath);
	GAE_Texture_t* texture = GAE_Texture_createFromFile(textureFile);

	if (GAE_FALSE == GAE_Texture_load(texture, GAE_FALSE)) {
		GAE_Sprite_delete(sprite);
		return 0;
	}

	SDL_Rect* src = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	SDL_Rect* dest = (SDL_Rect*)malloc(sizeof(SDL_Rect));

	sprite->texture = texture;

	src->x = 0;
	src->y = 0;
	src->w = texture->width;
	src->h = texture->height;

	dest->x = 0;
	dest->y = 0;
	dest->w = texture->width;
	dest->h = texture->height;

	sprite->src = src;
	sprite->dest = dest;

	return sprite;
}

void GAE_Sprite_delete(GAE_Sprite_t* sprite) {
	GAE_Texture_delete(sprite->texture);

	free(sprite);
	sprite = 0;
}
