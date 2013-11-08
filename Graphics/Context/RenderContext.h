#ifndef _RENDER_CONTEXT_H_
#define _RENDER_CONTEXT_H_

#if defined(SDL2)
#include "SDL2/SDL2RenderContext.h"
#elif defined(GLX)
#include "GLX/GLXRenderContext.h"
#elif defined(ANDROID)
#include "Android/AndroidRenderContext.h"
#elif defined(PANDORA)
#include "Pandora/PandoraRenderContext.h"
#endif

#endif

