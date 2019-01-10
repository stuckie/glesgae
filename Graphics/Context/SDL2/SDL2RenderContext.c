#include "SDL2RenderContext.h"

#include "../../Renderer/SDL2/SDL2Renderer.h"
#include "../../Window/RenderWindow.h"
#include <stdlib.h>
#include "SDL2/SDL.h"

GAE_RenderContext_t* GAE_RenderContext_create(void) {
	GAE_RenderContext_t* context = (GAE_RenderContext_t*)malloc(sizeof(GAE_RenderContext_t));

	context->renderer = 0;
	context->window = 0;

	return context;
}

void GAE_RenderContext_delete(GAE_RenderContext_t* context) {
	free(context);
	context = 0;
}

GAE_RenderContext_t* GAE_RenderContext_init(GAE_RenderContext_t* context) {
	return context;
}

GAE_RenderContext_t* GAE_RenderContext_shutdown(GAE_RenderContext_t* context) {
	return context;
}

GAE_RenderContext_t* GAE_RenderContext_update(GAE_RenderContext_t* context) {
	SDL_RenderPresent(context->renderer->renderer);
#if !defined(__EMSCRIPTEN__)
	SDL_RenderClear(context->renderer->renderer);
#endif
	return context;
}
