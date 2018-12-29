#ifndef _GRAPHICS_SYSTEM_H_
#define _GRAPHICS_SYSTEM_H_

struct GAE_RenderWindow_s;
struct GAE_RenderContext_s;
struct GAE_Renderer_s;
struct GAE_Sprite_s;

/* These need to be filled in via the users, as they're all dependent on what the user wants, really */
typedef struct GAE_GraphicsSystem_s {
	struct GAE_RenderWindow_s* window;
	struct GAE_RenderContext_s* context;
	struct GAE_Renderer_s* renderer;
} GAE_GraphicsSystem_t;

GAE_GraphicsSystem_t* GAE_GraphicsSystem_create(void);
GAE_GraphicsSystem_t* GAE_GraphicsSystem_drawSprite(GAE_GraphicsSystem_t* system, struct GAE_Sprite_s* const sprite);
void GAE_GraphicsSystem_delete(GAE_GraphicsSystem_t* system);

#endif
