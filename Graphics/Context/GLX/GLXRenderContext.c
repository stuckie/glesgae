#include "GLXRenderContext.h"

#include "../../Window/RenderWindow.h"
#include <stdlib.h>

GAE_RenderContext_t* GAE_RenderContext_create(void) {
	GAE_RenderContext_t* context = malloc(sizeof(GAE_RenderContext_t));

	context->window = 0;
	context->context = 0;

	return context;
}

void GAE_RenderContext_delete(GAE_RenderContext_t* context) {
	if (0 != context->context)
		GAE_RenderContext_shutdown(context);

	free(context);
	context = 0;
}

GAE_RenderContext_t* GAE_RenderContext_init(GAE_RenderContext_t* context) {
	GAE_X11_RenderWindow_t* x11Window = (GAE_X11_RenderWindow_t*)context->window->platform;

	int errorBase, eventBase;
	int visualArgs[]  = {
		GLX_RGBA
	,	GLX_DEPTH_SIZE, 16
	,	GLX_DOUBLEBUFFER
	,	None
	};
	XVisualInfo* visualInfo = 0;

	if (0 == glXQueryExtension(x11Window->display, &errorBase, &eventBase)) {
	}

	visualInfo = glXChooseVisual(x11Window->display, XDefaultScreen(x11Window->display), visualArgs);
	if (0 == visualInfo) {
	}
	
	context->context = glXCreateContext(x11Window->display, visualInfo, 0, 1);
	if (0 == context->context) {
	}
	
	free(visualInfo);
	
	glXMakeCurrent(x11Window->display, x11Window->window, context->context);
	
	glViewport(0, 0, context->window->width, context->window->height);
	glScissor(0, 0, context->window->width, context->window->height);
	
	glClearColor(0.4F, 0.4F, 0.4F, 0.0F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return context;
}

GAE_RenderContext_t* GAE_RenderContext_shutdown(GAE_RenderContext_t* context) {
	GAE_X11_RenderWindow_t* x11Window = (GAE_X11_RenderWindow_t*)context->window->platform;
	glXDestroyContext(x11Window->display, context->context);
	context->context = 0;
	glXMakeCurrent(x11Window->display, 0, 0);

	return context;
}

GAE_RenderContext_t* GAE_RenderContext_update(GAE_RenderContext_t* context) {
	GAE_X11_RenderWindow_t* x11Window = (GAE_X11_RenderWindow_t*)context->window->platform;
	glDisable(GL_SCISSOR_TEST);
	
	glXSwapBuffers(x11Window->display, x11Window->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_SCISSOR_TEST);

	return context;
}
