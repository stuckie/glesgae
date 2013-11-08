#ifndef _GL_TEXTURE_H_
#define _GL_TEXTURE_H_

typedef enum GAE_GL_Texture_Format_e {
	GAE_GL_TEXTURE_FORMAT_INVALID
,	GAE_GL_TEXTURE_FORMAT_DXT1
,	GAE_GL_TEXTURE_FORMAT_DXT5
,	GAE_GL_TEXTURE_FORMAT_RGBA
,	GAE_GL_TEXTURE_FORMAT_RGB
} GAE_GL_Texture_Format;

typedef enum GAE_GL_Texture_Filter_e {
	GAE_GL_TEXTURE_FILTER_NONE
,	GAE_GL_TEXTURE_FILTER_BILINEAR
,	GAE_GL_TEXTURE_FILTER_TRILINEAR
} GAE_GL_Texture_Filter;

typedef struct GAE_GL_Texture_s {
	unsigned int id;
	GAE_GL_Texture_Format format;
	GAE_GL_Texture_Filter filter;
} GAE_GL_Texture_t;

#endif
