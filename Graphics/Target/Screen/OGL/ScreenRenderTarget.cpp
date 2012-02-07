#include "../ScreenRenderTarget.h"

#include "../../../Context/Linux/GLee.h"

using namespace GLESGAE;

void ScreenRenderTarget::bind()
{
	// As per OpenGL Reference Manual, id 0 is kept for the Screen.
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ScreenRenderTarget::unbind()
{
	// Unbinding the screen shouldn't cause a crash, but should cause undefined behaviour for obvious reasons
	glBindFramebuffer(GL_FRAMEBUFFER, GL_INVALID_VALUE);
}
