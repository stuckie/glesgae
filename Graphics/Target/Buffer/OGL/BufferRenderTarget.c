#include "../BufferRenderTarget.h"

#if defined(GLX)
#include "../../../Context/GLX/GLee.h"
#endif

#include "../../../../GAE_Types.h"

GAE_RenderTarget_Buffer_t* GAE_RenderTarget_Buffer_create(const GAE_RenderTarget_Type type, const GAE_RenderTarget_Options options) {
	GAE_UNUSED(type);
	GAE_UNUSED(options);

	return 0;
}

GAE_RenderTarget_Buffer_t* GAE_RenderTarget_Buffer_bind(GAE_RenderTarget_Buffer_t* target) {
	return target;
}

GAE_RenderTarget_Buffer_t* GAE_RenderTarget_Buffer_unbind(GAE_RenderTarget_Buffer_t* target) {
	return target;
}

void GAE_RenderTarget_Buffer_delete(GAE_RenderTarget_Buffer_t* target) {
	GAE_UNUSED(target);
}
