#ifndef _TEXTURE_RENDER_TARGET_H_
#define _TEXTURE_RENDER_TARGET_H_

#include "../RenderTarget.h"

typedef struct GAE_RenderTarget_Texture_s {
	GAE_RenderTarget_t parent;
	struct GAE_Texture_s* texture;
	unsigned int fb;
	unsigned int rb;
} GAE_RenderTarget_Texture_t;

GAE_RenderTarget_Texture_t* GAE_RenderTarget_Texture_create(const GAE_RenderTarget_Type type, const GAE_RenderTarget_Options options);
GAE_RenderTarget_Texture_t* GAE_RenderTarget_Texture_bind(GAE_RenderTarget_Texture_t* target);
GAE_RenderTarget_Texture_t* GAE_RenderTarget_Texture_unbind(GAE_RenderTarget_Texture_t* target);
void GAE_RenderTarget_Texture_delete(GAE_RenderTarget_Texture_t* target);

#endif
