#if defined(GLES1)

#include "../ScreenRenderTarget.h"

#if defined(PANDORA) || defined(ANDROID)
	#include <GLES/gl.h>
#endif

using namespace GLESGAE;

void ScreenRenderTarget::bind()
{
	// As per OpenGL Reference Manual, id 0 is kept for the Screen.
	//glBindFramebufferOES(GL_FRAMEBUFFER_OES, 0);
}

void ScreenRenderTarget::unbind()
{
	// Unbinding the screen shouldn't cause a crash, but should cause undefined behaviour for obvious reasons
	//glBindFramebufferOES(GL_FRAMEBUFFER_OES, GL_INVALID_VALUE);
}

#endif

