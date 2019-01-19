#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../GAE_Types.h"

struct GAE_Buffer_s;

typedef struct GAE_Texture_s {
	unsigned int width;
	unsigned int height;
	void* platform;
} GAE_Texture_t;

#define GAE_TEXTURE_FROM_FILE (unsigned int)(-1)

/* Create a new Texture construct */
GAE_Texture_t* GAE_Texture_create();

/* Delete a Texture */
void GAE_Texture_delete(GAE_Texture_t* texture);

/* Load the given buffer into the texture, with possible width and height - use GAE_TEXTURE_FROM_FILE if unknown */
GAE_BOOL GAE_Texture_load(GAE_Texture_t* texture, struct GAE_Buffer_s* const buffer, const unsigned int width, const unsigned int height);

/* Saves the texture to the given buffer */
GAE_BOOL GAE_Texture_save(GAE_Texture_t* texture, struct GAE_Buffer_s* buffer);

#if defined(SDL2)
#include "Texture/SDL2/SDL2Texture.h"
#elif defined(GLES2) || defined(GLX)
#include "Texture/GL/GLTexture.h"
#endif

#endif

