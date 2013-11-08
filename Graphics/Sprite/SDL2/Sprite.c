#include "../../Sprite.h"

#include "../../Texture.h"
#include "../../../File/File.h"
#include "SDL.h"

#include <stdlib.h>
#include <string.h>

GAE_Sprite_t* GAE_Sprite_create(const char* texturePath) {
	GAE_Sprite_t* sprite = malloc(sizeof(GAE_Sprite_t));

	GAE_File_t* textureFile = GAE_File_create(texturePath);
	GAE_Texture_t* texture = GAE_Texture_createFromFile(textureFile);
	GAE_Texture_load(texture, GAE_FALSE);

	sprite->texture = texture;
	sprite->srcRect = NULL;
	sprite->dstRect = NULL;

	return sprite;
}

void GAE_Sprite_delete(GAE_Sprite_t* sprite) {
	GAE_Texture_delete(sprite->texture);

	free(sprite);
	sprite = 0;
}
