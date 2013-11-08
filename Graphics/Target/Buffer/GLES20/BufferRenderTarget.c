#if defined(GLES2)

#include "../BufferRenderTarget.h"

GAE_RenderTarget_Buffer_t* GAE_RenderTarget_Buffer_create(const GAE_RenderTarget_Type /*type*/, const GAE_RenderTarget_Options /*options*/) {
	return 0;
}

GAE_RenderTarget_Buffer_t* GAE_RenderTarget_Buffer_bind(GAE_RenderTarget_Screen_t* target) {
	return target;
}

GAE_RenderTarget_Buffer_t* GAE_RenderTarget_Buffer_unbind(GAE_RenderTarget_Screen_t* target) {
	return target;
}

void GAE_RenderTarget_Buffer_delete(GAE_RenderTarget_Buffer_t* /*target*/) {
}

#endif

