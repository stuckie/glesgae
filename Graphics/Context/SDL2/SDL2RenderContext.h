#ifndef _SDL2_RENDER_CONTEXT_H_
#define _SDL2_RENDER_CONTEXT_H_

struct GAE_RenderWindow_s;
struct GAE_Renderer_s;

typedef struct GAE_RenderContext_s {
	struct GAE_RenderWindow_s* window;
	struct GAE_Renderer_s* renderer;
} GAE_RenderContext_t;

GAE_RenderContext_t* GAE_RenderContext_create(void);
GAE_RenderContext_t* GAE_RenderContext_init(GAE_RenderContext_t* context);
GAE_RenderContext_t* GAE_RenderContext_update(GAE_RenderContext_t* context);
GAE_RenderContext_t* GAE_RenderContext_shutdown(GAE_RenderContext_t* context);
void GAE_RenderContext_delete(GAE_RenderContext_t* context);


#endif
