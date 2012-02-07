#include "ScreenRenderTarget.h"

#if defined(PANDORA)
	#include <GLES2/gl.h>
#endif

void ScreenRenderTarget::bind()
{
	// As per OpenGL Reference Manual, id 0 is kept for the Screen.
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void ScreenRenderTarget::unbind()
{
	// Unbinding the screen shouldn't cause a crash, but should cause undefined behaviour for obvious reasons
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, GL_INVALID_VALUE);
}
