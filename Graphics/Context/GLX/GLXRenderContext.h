#ifndef _GLX_RENDER_CONTEXT_H_
#define _GLX_RENDER_CONTEXT_H_

#include "GLee.h"

struct GAE_RenderWindow_s;

typedef struct GAE_RenderContext_s {
	struct GAE_RenderWindow_s* window;
	GLXContext context;
} GAE_RenderContext_t;

GAE_RenderContext_t* GAE_RenderContext_create(void);
GAE_RenderContext_t* GAE_RenderContext_init(GAE_RenderContext_t* context);
GAE_RenderContext_t* GAE_RenderContext_update(GAE_RenderContext_t* context);
GAE_RenderContext_t* GAE_RenderContext_shutdown(GAE_RenderContext_t* context);
void GAE_RenderContext_delete(GAE_RenderContext_t* context);


#endif
