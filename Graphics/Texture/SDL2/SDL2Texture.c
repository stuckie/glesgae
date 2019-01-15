#include "../../Texture.h"

#include <assert.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

#include "../../../Utils/HashString.h"
#include "../../../File/File.h"
#include "../../GraphicsSystem.h"
#include "../../Renderer/SDL2/SDL2Renderer.h"
#include "../../../Platform/Platform.h"
#include "../../../External/stb/stb_image.h"
#include "../../../Utils/Logger.h"

SDL_Texture* loadTextureFromFile(GAE_Texture_t* texture);
SDL_Texture* loadTextureFromBuffer(GAE_Texture_t* texture);

GAE_Texture_t* GAE_Texture_createFromFile(GAE_File_t* const image) {
	GAE_Texture_t* texture = (GAE_Texture_t*)malloc(sizeof(GAE_Texture_t));
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)malloc(sizeof(GAE_SDL2_Texture_t));

	texture->file = image;
	texture->width = 0U;
	texture->height = 0U;
	texture->type = GAE_TEXTURE_TYPE_FILE;

	platform->texture = 0;
	platform->format = 0;
	platform->access = 0;
	platform->renderer = GAE_PLATFORM->graphicsSystem->renderer->renderer;

	texture->platform = (void*)platform;

	return texture;
}

GAE_Texture_t* GAE_Texture_createFromBuffer(GAE_File_t* const buffer, const unsigned int width, const unsigned int height) {
	GAE_Texture_t* texture = (GAE_Texture_t*)malloc(sizeof(GAE_Texture_t));
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)malloc(sizeof(GAE_SDL2_Texture_t));

	texture->file = buffer;
	texture->width = width;
	texture->height = height;
	texture->type = GAE_TEXTURE_TYPE_BUFFER;

	platform->texture = 0;
	platform->format = 0;
	platform->access = 0;

	texture->platform = (void*)platform;

	return texture;
}

GAE_Texture_t* GAE_Texture_createFromSurface(SDL_Renderer* renderer, SDL_Surface* surface) {
	GAE_Texture_t* texture = (GAE_Texture_t*)malloc(sizeof(GAE_Texture_t));
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)malloc(sizeof(GAE_SDL2_Texture_t));

	texture->file = 0;
	texture->width = 0;
	texture->height = 0;
	texture->type = GAE_TEXTURE_TYPE_BUFFER;

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

	if (0 != texture->file)
		GAE_File_delete(texture->file);

	free(platform);
	free(texture);
	texture = 0;
}

GAE_BOOL GAE_Texture_load(GAE_Texture_t* texture, const GAE_BOOL retainData) {
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)texture->platform;

	GAE_File_t* file = texture->file;
	GAE_FILE_STATUS openStatus;
	GAE_FILE_READ_STATUS readStatus;

	if (0 != platform->texture) {
		GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Texture already loaded: %s\n", file->filePath);
		return GAE_FALSE;
	}
	
	switch (texture->type) {
		case GAE_TEXTURE_TYPE_FILE: {
			if (0 == file->buffer) {
				GAE_File_open(texture->file, GAE_FILE_OPEN_READ, GAE_FILE_BINARY, &openStatus);
				if (GAE_FILE_ERROR == openStatus) {
					GAE_File_close(texture->file, GAE_FILE_CLOSE_DELETE_DATA, NULL);
					GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Failed to open Texture: %s\n", file->filePath);
					return GAE_FALSE;
				}
				GAE_File_read(texture->file, GAE_FILE_READ_ALL, &readStatus);
				if (GAE_FILE_READ_ERROR == readStatus) {
					GAE_File_close(texture->file, GAE_FILE_CLOSE_DELETE_DATA, NULL);
					GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Failed to read Texture: %s\n", file->filePath);
					return GAE_FALSE;
				}
			}

			platform->texture = loadTextureFromFile(texture);

			if (0 == platform->texture) {
				GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Texture loading error: %s\n", file->filePath);
				GAE_File_close(texture->file, GAE_FILE_CLOSE_DELETE_DATA, NULL);
				return GAE_FALSE;
			}
			
			retainData ? GAE_File_close(texture->file, GAE_FILE_CLOSE_RETAIN_DATA, &openStatus) : GAE_File_close(texture->file, GAE_FILE_CLOSE_DELETE_DATA, &openStatus);
			if (GAE_FILE_ERROR == openStatus) {
				GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Failed to close Texture: %s\n", file->filePath);
				return GAE_FALSE;
			}
			break;
		}
		case GAE_TEXTURE_TYPE_BUFFER: {
			platform->texture = loadTextureFromBuffer(texture);

			if (GAE_FALSE == retainData)
				GAE_File_delete(texture->file);

			if (0 == platform->texture) {
				GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Texture creation error: %s\n", file->filePath);
				return GAE_FALSE;
			}

			break;
		}
	}
	
	return GAE_TRUE;
}

/* todo: unimplemented */
GAE_BOOL GAE_Texture_save(GAE_Texture_t* texture) {
	GAE_UNUSED(texture);
	return GAE_FALSE;
}

SDL_Texture* loadTextureFromFile(GAE_Texture_t* texture) {
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)texture->platform;
	GAE_File_t* file = texture->file;

	int oFormat, width, height, depth, pitch;
    Uint32 rmask, gmask, bmask, amask;
    int nFormat = STBI_rgb_alpha;
    unsigned char* data = stbi_load_from_memory(file->buffer, file->bufferSize, &width, &height, &oFormat, nFormat);
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

SDL_Texture* loadTextureFromBuffer(GAE_Texture_t* texture) {
	GAE_SDL2_Texture_t* platform = (GAE_SDL2_Texture_t*)texture->platform;
	unsigned int imageSize = 0U;
	SDL_Texture* tex = 0;

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
	
	if (imageSize != texture->file->bufferSize) {
		GAE_Logger_log(GAE_PLATFORM->logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_DEFAULT, "Texture: Expected size of: %d, buffer size is %d\n", imageSize, texture->file->bufferSize);
		return tex;
	}
	
	tex = SDL_CreateTexture(platform->renderer, platform->format, platform->access, texture->width, texture->height);
	
	return tex;
}
