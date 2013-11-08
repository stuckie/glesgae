#ifndef _BUFFER_RENDER_TARGET_H_
#define _BUFFER_RENDER_TARGET_H_

#include "../RenderTarget.h"

typedef struct GAE_RenderTarget_Buffer_s {
	GAE_RenderTarget_t parent;
} GAE_RenderTarget_Buffer_t;

GAE_RenderTarget_Buffer_t* GAE_RenderTarget_Buffer_create(const GAE_RenderTarget_Type type, const GAE_RenderTarget_Options options);
GAE_RenderTarget_Buffer_t* GAE_RenderTarget_Buffer_bind(GAE_RenderTarget_Buffer_t* target);
GAE_RenderTarget_Buffer_t* GAE_RenderTarget_Buffer_unbind(GAE_RenderTarget_Buffer_t* target);
void GAE_RenderTarget_Buffer_delete(GAE_RenderTarget_Buffer_t* target);

#endif
