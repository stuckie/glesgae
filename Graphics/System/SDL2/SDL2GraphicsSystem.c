#include "../../GraphicsSystem.h"
#include "../../Renderer/Renderer.h"
#include "../../Sprite.h"

#include <stdlib.h>

GAE_GraphicsSystem_t* GAE_GraphicsSystem_create() {
	GAE_GraphicsSystem_t* system = malloc(sizeof(GAE_GraphicsSystem_t));
	system->window = 0;
	system->context = 0;
	system->renderer = 0;

	return system;
}

GAE_GraphicsSystem_t* GAE_GraphicsSystem_drawSprite(GAE_GraphicsSystem_t* system, GAE_Sprite_t* const sprite) {
	GAE_Renderer_drawSprite(system->renderer, sprite);

	return system;
}

GAE_GraphicsSystem_t* GAE_GraphicsSystem_blitTexture(GAE_GraphicsSystem_t* system, struct GAE_Texture_s* const texture, struct GAE_Rect_s* src, struct GAE_Rect_s* dst) {
	GAE_Renderer_blitTexture(system->renderer, texture, src, dst);
	
	return system;
}

void GAE_GraphicsSystem_delete(GAE_GraphicsSystem_t* system) {
	free(system);
	system = 0;
}
