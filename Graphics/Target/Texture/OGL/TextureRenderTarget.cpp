#include "../TextureRenderTarget.h"

#include "../../../Platform/Application.h"
#include "../../../Utils/Logger.h"

#if defined(LINUX)
#include "../../../Context/Linux/GLee.h"
#endif

using namespace GLESGAE;

TextureRenderTarget::TextureRenderTarget(const RenderTarget::Options options)
: RenderTarget(RenderTarget::TARGET_TEXTURE, options)
, mTexture(0)
, mFB(GL_INVALID_VALUE)
, mRB(GL_INVALID_VALUE)
{
	glGenFramebuffers(1, &mFB);
	
	if (options == OPTIONS_WITH_DEPTH)
		glGenRenderbuffers(1, &mRB);
}

TextureRenderTarget::~TextureRenderTarget()
{
	if (mFB != GL_INVALID_VALUE)
		glDeleteFramebuffers(1, &mFB);
	if (mRB != GL_INVALID_VALUE)
		glDeleteRenderbuffers(1, &mRB);
}

void TextureRenderTarget::bind()
{
	if (mTexture == 0) {
		Application::getInstance()->getLogger()->log("TextureRenderTarget: No Texture Bound\n", Logger::LOG_TYPE_ERROR);
		return;
	}
	
	if (mFB != GL_INVALID_VALUE) {
		glBindFramebuffer(GL_FRAMEBUFFER, mFB);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture->getId(), 0);
	}
	
	if (mRB != GL_INVALID_VALUE) {
		glBindRenderbuffer(GL_RENDERBUFFER, mRB);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, mTexture->getWidth(), mTexture->getHeight());
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRB);
	}
}

void TextureRenderTarget::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, GL_INVALID_VALUE);
	glBindRenderbuffer(GL_RENDERBUFFER, GL_INVALID_VALUE);
}
