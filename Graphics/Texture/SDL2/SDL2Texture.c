#include "../../Texture.h"

#include <assert.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

#include "../../../Utils/HashString.h"
#include "../../../Buffer/Buffer.h"
#include "../../GraphicsSystem.h"
#include "../../Renderer/SDL2/SDL2Renderer.h"
#include "../../../Platform/Platform.h"
#include "../../../External/stb/stb_image.h"
#include "../../../Utils/Logger.h"

SDL_Texture* loadTextureFromFile(GAE_Texture_t* texture, GAE_Buffer_t* const buffer);
SDL_Texture* loadTextureFromBuffer(GAE_Texture_t* texture, GAE_Buffer_t* const buffer);

GAE_Texture_t* GAE_Texture_create() {
	GAE_Texture_t* texture = (GAE_Texture_t*)malloc(sizeof(GAE_Texture_t));
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)malloc(sizeof(GAE_SDL2_Texture_t));

	texture->width = GAE_TEXTURE_FROM_FILE;
	texture->height = GAE_TEXTURE_FROM_FILE;

	platform->texture = 0;
	platform->format = 0;
	platform->access = 0;
	platform->renderer = GAE_PLATFORM->graphicsSystem->renderer->renderer;

	texture->platform = (void*)platform;

	return texture;
}

GAE_Texture_t* GAE_Texture_createFromSurface(SDL_Renderer* renderer, SDL_Surface* surface) {
	GAE_Texture_t* texture = (GAE_Texture_t*)malloc(sizeof(GAE_Texture_t));
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)malloc(sizeof(GAE_SDL2_Texture_t));

	texture->width = 0;
	texture->height = 0;

	platform->texture = SDL_CreateTextureFromSurface(renderer, surface);
	assert(platform->texture);
	SDL_QueryTexture(platform->texture, &platform->format, &platform->access, (int*)&texture->width, (int*)&texture->height);

	texture->platform = platform;

	return texture;
}

void GAE_Texture_delete(GAE_Texture_t* texture) {
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)texture->platform;

	if (0 != platform->texture)
		SDL_DestroyTexture(platform->texture);

	free(platform);
	free(texture);
	texture = 0;
}

GAE_BOOL GAE_Texture_load(GAE_Texture_t* texture, GAE_Buffer_t* const buffer, const unsigned int width, const unsigned int height) {
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)texture->platform;

	if (0 != platform->texture) {
		GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Texture already loaded\n");
		return GAE_FALSE;
	}
	
	if (width == GAE_TEXTURE_FROM_FILE || height == GAE_TEXTURE_FROM_FILE || width != texture->width || height != texture->height)
		platform->texture = loadTextureFromFile(texture, buffer);
	else
		platform->texture = loadTextureFromBuffer(texture, buffer);

	if (0 == platform->texture) {
		GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Texture creation error\n");
		return GAE_FALSE;
	}
	
	return GAE_TRUE;
}

/* todo: unimplemented */
GAE_BOOL GAE_Texture_save(GAE_Texture_t* texture, GAE_Buffer_t* buffer) {
	GAE_UNUSED(texture);
	GAE_UNUSED(buffer);
	return GAE_FALSE;
}

SDL_Texture* loadTextureFromFile(GAE_Texture_t* texture, GAE_Buffer_t* const buffer) {
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)texture->platform;

	int oFormat, width, height, depth, pitch;
    Uint32 rmask, gmask, bmask, amask;
    int nFormat = STBI_rgb_alpha;
    unsigned char* data = stbi_load_from_memory(buffer->data, buffer->length, &width, &height, &oFormat, nFormat);
	SDL_Surface* surf = 0;
	SDL_Texture* tex = 0;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        int shift = (STBI_rgb == nFormat) ? 8 : 0;
        rmask = 0xff000000 >> shift;
        gmask = 0x00ff0000 >> shift;
        bmask = 0x0000ff00 >> shift;
        amask = 0x000000ff >> shift;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = (STBI_rgb == nFormat) ? 0 : 0xff000000;
    #endif

    if (STBI_rgb == nFormat) {
        depth = 24;
        pitch = 3 * width; /* 3 bytes per pixel * pixels per row */
    } else {
        depth = 32;
        pitch = 4 * width;
    }

    surf = SDL_CreateRGBSurfaceFrom((void*)data, width, height, depth, pitch,
                                                rmask, gmask, bmask, amask);

	
	tex = SDL_CreateTextureFromSurface(platform->renderer, surf);
	SDL_QueryTexture(tex, &platform->format, &platform->access, (int*)&texture->width, (int*)&texture->height);
	SDL_FreeSurface(surf);
	stbi_image_free(data);

	return tex;
}

SDL_Texture* loadTextureFromBuffer(GAE_Texture_t* texture, GAE_Buffer_t* const buffer) {
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)texture->platform;
	unsigned int imageSize = 0U;
	SDL_Texture* tex = 0;
	SDL_Surface* surf = 0;

	switch (platform->format) {
		case SDL_PIXELFORMAT_RGB888:
			imageSize = texture->width * texture->height * 3;
			break;
		case SDL_PIXELFORMAT_RGBA8888:
			imageSize = texture->width * texture->height * 4;
			break;
		default:
			GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Invalid Texture Format specified\n");
			return tex;
	}
	
	if (imageSize != buffer->length) {
		GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Texture: Expected size of: %d, buffer size is %d\n", imageSize, buffer->length);
		return tex;
	}
	
	surf = SDL_CreateRGBSurfaceWithFormatFrom((void*)buffer->data, texture->width, texture->height, 32, 4 * texture->width, platform->format);
	tex = SDL_CreateTextureFromSurface(platform->renderer, surf);
	SDL_FreeSurface(surf);
	
	return tex;
}

