#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../GAE_Types.h"

struct GAE_File_s;

typedef enum GAE_Texture_Type_e {
	GAE_TEXTURE_TYPE_FILE
,	GAE_TEXTURE_TYPE_BUFFER
} GAE_Texture_Type;

typedef struct GAE_Texture_s {
	struct GAE_File_s* file;
	unsigned int width;
	unsigned int height;
	GAE_Texture_Type type;
	void* platform;
} GAE_Texture_t;

GAE_Texture_t* GAE_Texture_createFromFile(struct GAE_File_s* const image);
GAE_Texture_t* GAE_Texture_createFromBuffer(struct GAE_File_s* const buffer, const unsigned int width, const unsigned int height);
void GAE_Texture_delete(GAE_Texture_t* texture);

GAE_BOOL GAE_Texture_load(GAE_Texture_t* texture, const GAE_BOOL retainData);
GAE_BOOL GAE_Texture_save(GAE_Texture_t* texture);

#if defined(SDL2)
#include "Texture/SDL2/SDL2Texture.h"
#elif defined(GLES2) || defined(GLX)
#include "Texture/GL/GLTexture.h"
#endif

#endif

