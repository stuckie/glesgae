#if defined(GLES2)

#include "../ScreenRenderTarget.h"

#if defined(PANDORA) || defined(ANDROID)
	#include <GLES2/gl2.h>
#endif

GAE_RenderTarget_Screen_t* GAE_RenderTarget_Screen_create(const GAE_RenderTarget_Type type, const GAE_RenderTarget_Options options) {
	GAE_RenderTarget_Screen_t* target = malloc(sizeof(GAE_RenderTarget_Screen_t));
	target->parent.type = type;
	target->parent.options = options;

	return target;
}

GAE_RenderTarget_Screen_t* GAE_RenderTarget_Screen_bind(GAE_RenderTarget_Screen_t* target) {
	glBindFramebuffer(GL_FRAMEBUFFER, 0); /* As per OpenGL Reference Manual, 0 is kept for the screen */

	return target;
}

GAE_RenderTarget_Screen_t* GAE_RenderTarget_Screen_unbind(GAE_RenderTarget_Screen_t* target) {
	glBindFramebuffer(GL_FRAMEBUFFER, GL_INVALID_VALUE); /* Unbinding the screen shouldn't crash, but should cause undefined behaviour */

	return target;
}

void GAE_RenderTarget_Screen_delete(GAE_RenderTarget_Screen_t* target) {
	free(target);
	target = 0;
}


#endif

