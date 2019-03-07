#include "../../Renderer/Renderer.h"
#include "../../GraphicsSystem.h"
#include "../../Sprite.h"

#include <stdlib.h>

GAE_GraphicsSystem_t* GAE_GraphicsSystem_create() {
	GAE_GraphicsSystem_t* system = malloc(sizeof(GAE_GraphicsSystem_t));
	system->window = 0;
	system->context = 0;
	system->renderer = 0;

	return system;
}

GAE_GraphicsSystem_t* GAE_GraphicsSystem_clear(GAE_GraphicsSystem_t* system) {
	return system;
}

GAE_GraphicsSystem_t* GAE_GraphicsSystem_drawSprite(GAE_GraphicsSystem_t* system, GAE_Sprite_t* const sprite) {
	GAE_Renderer_drawSprite(system->renderer, sprite);

	return system;
}

GAE_GraphicsSystem_t* GAE_GraphicsSystem_present(GAE_GraphicsSystem_t* system) {
	return system;
}

void GAE_GraphicsSystem_delete(GAE_GraphicsSystem_t* system) {
	free(system);
	system = 0;
}
