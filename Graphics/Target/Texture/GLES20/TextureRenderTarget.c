#if defined(GLES2)
#include "../TextureRenderTarget.h"

#if defined(PANDORA) || defined(ANDROID)
	#include <GLES2/gl2.h>
#endif

GAE_RenderTarget_Texture_t* GAE_RenderTarget_Texture_create(const GAE_RenderTarget_Type type, const GAE_RenderTarget_Options options) {
	GAE_RenderTarget_Texture_t* target = malloc(sizeof(GAE_RenderTarget_Texture_t));
	target->parent.type = type;
	target->parent.options = options;

	target->texture = 0;
	target->fb = GL_INVALID_VALUE;
	target->rb = GL_INVALID_VALUE;
	glGenFramebuffers(1, &target->fb);

	if (options == GAE_RENDERTARGET_OPTIONS_WITH_DEPTH)
		glGenRenderbuffers(1, &target->rb);

	return target;
}

GAE_RenderTarget_Texture_t* GAE_RenderTarget_Texture_bind(GAE_RenderTarget_Texture_t* target) {
	GAE_GL_Texture_t* texture = (GAE_GL_Texture_t*)target->texture;
	if (0 == texture) {
		/*Application::getInstance()->getLogger()->log("TextureRenderTarget: No Texture Bound\n", Logger::LOG_TYPE_ERROR);*/
		return target;
	}
	
	if (GL_INVALID_VALUE != target->fb) {
		glBindFramebuffer(GL_FRAMEBUFFER, target->fb);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->id, 0);
	}
	
	if (GL_INVALID_VALUE != target->rb) {
		glBindRenderbuffer(GL_RENDERBUFFER, target->rb);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, target->texture->width, target->texture->height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, target->rb);
	}

	return target;
}

GAE_RenderTarget_Texture_t* GAE_RenderTarget_Texture_unbind(GAE_RenderTarget_Texture_t* target) {
	glBindFramebuffer(GL_FRAMEBUFFER, GL_INVALID_VALUE);
	glBindRenderbuffer(GL_RENDERBUFFER, GL_INVALID_VALUE);
}

void GAE_RenderTarget_Texture_delete(GAE_RenderTarget_Texture_t* target) {
	if (GL_INVALID_VALUE != target->fb)
		glDeleteFramebuffers(1, &target->fb)
	if (GL_INVALID_VALUE != target->rb)
		glDeleteRenderbuffers(1, &target->rb)

	free(target);
	target = 0;
}

#endif
