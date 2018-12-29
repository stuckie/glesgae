#ifndef _RENDERER_H_
#define _RENDERER_H_

#if defined(SDL2)
#include "SDL2/SDL2Renderer.h"
#elif defined(GLX)
#include "GLES20/ShaderGLVboRenderer.h"
#elif defined(ANDROID)
#include "GLES20/ShaderGLVboRenderer.h"
#elif defined(PANDORA)
#include "GLES20/ShaderGLVboRenderer.h"
#endif

#endif
