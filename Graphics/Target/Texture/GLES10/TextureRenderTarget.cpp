#if defined(GLES1)
#include "../TextureRenderTarget.h"

#include "../../../../Platform/Application.h"
#include "../../../../Utils/Logger.h"

#if defined(PANDORA) || defined(ANDROID)
	#include <GLES/gl.h>
#endif

using namespace GLESGAE;

TextureRenderTarget::TextureRenderTarget(const RenderTarget::Options options)
: RenderTarget(RenderTarget::TARGET_TEXTURE, options)
, mTexture(0)
, mFB(GL_INVALID_VALUE)
, mRB(GL_INVALID_VALUE)
{
}

TextureRenderTarget::~TextureRenderTarget()
{
}

void TextureRenderTarget::bind()
{
}

void TextureRenderTarget::unbind()
{
}

#endif
