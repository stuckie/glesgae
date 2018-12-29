#include "SDL2Renderer.h"

#include <stdlib.h>
#include "SDL2/SDL.h"
#include "../../Window/RenderWindow.h"
#include "../../Sprite.h"
#include "../../Texture.h"
#include "../../../GAE_Types.h"

GAE_Renderer_t* GAE_Renderer_create(GAE_RenderWindow_t* const window) { /* default flags if we don't really care how we set up the renderer */
	return GAE_SDL2Renderer_create(window, -1, SDL_RENDERER_ACCELERATED);
}

GAE_Renderer_t* GAE_SDL2Renderer_create(GAE_RenderWindow_t* const window, const int index, const unsigned int flags) {
	GAE_Renderer_t* renderer = malloc(sizeof(GAE_Renderer_t));
	GAE_SDL2_RenderWindow_t* sdlWindow = (GAE_SDL2_RenderWindow_t*)window->platform;

	renderer->renderer = SDL_CreateRenderer(sdlWindow->window, index, flags);

	return renderer;
}

GAE_Renderer_t* GAE_Renderer_drawMesh(GAE_Renderer_t* renderer, struct GAE_Mesh_s* const mesh, GAE_Matrix4_t* const transform) {
	GAE_UNUSED(mesh);
	GAE_UNUSED(transform);

	return renderer;
}

GAE_Renderer_t* GAE_Renderer_drawSprite(GAE_Renderer_t* renderer, GAE_Sprite_t* const sprite) {
	GAE_SDL2_Texture_t* sdlTexture = (GAE_SDL2_Texture_t*)sprite->texture->platform;
	SDL_RenderCopy(renderer->renderer, sdlTexture->texture, sprite->src, sprite->dest);

	return renderer;
}

void GAE_Renderer_delete(GAE_Renderer_t* renderer) {
	SDL_DestroyRenderer(renderer->renderer);

	free(renderer);
	renderer = 0;
}
