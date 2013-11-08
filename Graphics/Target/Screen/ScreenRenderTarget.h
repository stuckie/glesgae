#ifndef _SCREEN_RENDER_TARGET_H_
#define _SCREEN_RENDER_TARGET_H_

#include "../RenderTarget.h"

typedef struct GAE_RenderTarget_Screen_s {
	GAE_RenderTarget_t parent;
} GAE_RenderTarget_Screen_t;

GAE_RenderTarget_Screen_t* GAE_RenderTarget_Screen_create(const GAE_RenderTarget_Type type, const GAE_RenderTarget_Options options);
GAE_RenderTarget_Screen_t* GAE_RenderTarget_Screen_bind(GAE_RenderTarget_Screen_t* target);
GAE_RenderTarget_Screen_t* GAE_RenderTarget_Screen_unbind(GAE_RenderTarget_Screen_t* target);
void GAE_RenderTarget_Screen_delete(GAE_RenderTarget_Screen_t* target);

#endif
