#ifndef _RENDER_TARGET_H_
#define _RENDER_TARGET_H_

typedef enum GAE_RenderTarget_Type_e {
	GAE_RENDERTARGET_TYPE_SCREEN
,	GAE_RENDERTARGET_TYPE_BUFFER
,	GAE_RENDERTARGET_TYPE_TEXTURE
} GAE_RenderTarget_Type;

typedef enum GAE_RenderTarget_Options_e {
	GAE_RENDERTARGET_OPTIONS_WITH_COLOUR
,	GAE_RENDERTARGET_OPTIONS_WITH_DEPTH
,	GAE_RENDERTARGET_OPTIONS_WITH_STENCIL
,	GAE_RENDERTARGET_OPTIONS_WITH_COLOUR_AND_DEPTH
,	GAE_RENDERTARGET_OPTIONS_WITH_COLOUR_AND_STENCIL
,	GAE_RENDERTARGET_OPTIONS_WITH_DEPTH_AND_STENCIL
,	GAE_RENDERTARGET_OPTIONS_WITH_COLOUR_DEPTH_AND_STENCIL
} GAE_RenderTarget_Options;

typedef struct GAE_RenderTarget_s {
	GAE_RenderTarget_Type type;
	GAE_RenderTarget_Options options;
} GAE_RenderTarget_t;

#endif
