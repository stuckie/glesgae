#if defined(GLES2)

#include "../BufferRenderTarget.h"

using namespace GLESGAE;

BufferRenderTarget::BufferRenderTarget(const RenderTarget::Options options)
: RenderTarget(RenderTarget::TARGET_BUFFER, options)
{
}

BufferRenderTarget::~BufferRenderTarget()
{
}

void BufferRenderTarget::bind()
{
}

void BufferRenderTarget::unbind()
{
}

#endif

