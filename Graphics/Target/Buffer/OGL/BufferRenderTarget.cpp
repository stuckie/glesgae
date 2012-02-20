#include "../BufferRenderTarget.h"

#if defined(LINUX)
#include "../../../Context/Linux/GLee.h"
#endif

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
