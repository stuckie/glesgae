#include "../TextureRenderTarget.h"

#include "SDL.h"

#include "../../../Texture.h"
#include <stdlib.h>

GAE_RenderTarget_Texture_t* GAE_RenderTarget_Texture_create(const GAE_RenderTarget_Type type, const GAE_RenderTarget_Options options) {
	GAE_RenderTarget_Texture_t* target = malloc(sizeof(GAE_RenderTarget_Texture_t));
	target->parent.type = type;
	target->parent.options = options;

	target->texture = 0;
	target->fb = 0;
	target->rb = 0;

	return target;
}

GAE_RenderTarget_Texture_t* GAE_RenderTarget_Texture_bind(GAE_RenderTarget_Texture_t* target) {
	GAE_SDL2_Texture_t* texture = (GAE_SDL2_Texture_t*)target->texture;

	if (0 == texture) {
		/*Application::getInstance()->getLogger()->log("TextureRenderTarget: No Texture Bound\n", Logger::LOG_TYPE_ERROR);*/
		return target;
	}

	/*TODO: Need to additionally check that flags have SDL_TEXTUREACCESS_TARGET or this will fail */
	
	SDL_SetRenderTarget(texture->renderer, texture->texture);

	return target;
}

GAE_RenderTarget_Texture_t* GAE_RenderTarget_Texture_unbind(GAE_RenderTarget_Texture_t* target) {
	GAE_SDL2_Texture_t* texture = (GAE_SDL2_Texture_t*)target->texture;
	SDL_SetRenderTarget(texture->renderer, NULL);

	return target;
}

void GAE_RenderTarget_Texture_delete(GAE_RenderTarget_Texture_t* target) {
	free(target);
	target = 0;
}
