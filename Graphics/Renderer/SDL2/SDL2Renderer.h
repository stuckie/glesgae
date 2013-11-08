#ifndef _SDL2_RENDERER_H_
#define _SDL2_RENDERER_H_

#include "../../../GAE_Types.h"

struct SDL_Renderer;
struct GAE_Sprite_s;
struct GAE_RenderWindow_s;
struct GAE_Mesh_s;

typedef struct GAE_Renderer_s {
	struct SDL_Renderer* renderer;
} GAE_Renderer_t;

GAE_Renderer_t* GAE_Renderer_create(struct GAE_RenderWindow_s* const window);
GAE_Renderer_t* GAE_SDL2Renderer_create(struct GAE_RenderWindow_s* const window, const int index, const unsigned int flags);
GAE_Renderer_t* GAE_Renderer_drawMesh(GAE_Renderer_t* renderer, struct GAE_Mesh_s* const mesh, GAE_Matrix4_t* const transform);
GAE_Renderer_t* GAE_Renderer_drawSprite(GAE_Renderer_t* renderer, struct GAE_Sprite_s* const sprite);
void GAE_Renderer_delete(GAE_Renderer_t* renderer);

#endif
