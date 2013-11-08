#include "../../Texture.h"

#include <assert.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"

#include "../../../Utils/HashString.h"
#include "../../../File/File.h"
#include "../../GraphicsSystem.h"
#include "../../Renderer/SDL2/SDL2Renderer.h"
#include "../../../Platform/Platform.h"

SDL_Texture* loadTextureFromFile(GAE_Texture_t* texture);
SDL_Texture* loadTextureFromBuffer(GAE_Texture_t* texture);

GAE_Texture_t* GAE_Texture_createFromFile(GAE_File_t* const image) {
	GAE_Texture_t* texture = malloc(sizeof(GAE_Texture_t));
	GAE_SDL2_Texture_t* platform = malloc(sizeof(GAE_SDL2_Texture_t));

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
	GAE_Texture_t* texture = malloc(sizeof(GAE_Texture_t));
	GAE_SDL2_Texture_t* platform = malloc(sizeof(GAE_SDL2_Texture_t));

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
	GAE_Texture_t* texture = malloc(sizeof(GAE_Texture_t));
	GAE_SDL2_Texture_t* platform = malloc(sizeof(GAE_SDL2_Texture_t));

	texture->file = 0;
	texture->width = 0;
	texture->height = 0;
	texture->type = GAE_TEXTURE_TYPE_BUFFER;

	platform->texture = SDL_CreateTextureFromSurface(renderer, surface);
	assert(platform->texture);
	SDL_QueryTexture(platform->texture, &platform->format, &platform->access, (int*)&texture->width, (int*)&texture->height);

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
		/*Application::getInstance()->getLogger()->log("Texture already loaded: " + mFile->getFilePath() + "\n", Logger::LOG_TYPE_ERROR);*/
		return GAE_FALSE;
	}
	
	switch (texture->type) {
		case GAE_TEXTURE_TYPE_FILE: {
			if (0 == file->buffer) {
				GAE_File_open(texture->file, GAE_FILE_OPEN_READ, GAE_FILE_BINARY, &openStatus);
				if (GAE_FILE_ERROR == openStatus) {
					GAE_File_close(texture->file, GAE_FILE_CLOSE_DELETE_DATA, NULL);
					/*Application::getInstance()->getLogger()->log("Failed to open Texture: " + mFile->getFilePath() + "\n", Logger::LOG_TYPE_ERROR);*/
					return GAE_FALSE;
				}
				GAE_File_read(texture->file, GAE_FILE_READ_ALL, &readStatus);
				if (GAE_FILE_READ_ERROR == readStatus) {
					GAE_File_close(texture->file, GAE_FILE_CLOSE_DELETE_DATA, NULL);
					/*Application::getInstance()->getLogger()->log("Failed to read Texture: " + mFile->getFilePath() + "\n", Logger::LOG_TYPE_ERROR);*/
					return GAE_FALSE;
				}
			}

			platform->texture = loadTextureFromFile(texture);

			if (0 == platform->texture) {
				/*Application::getInstance()->getLogger()->log("Texture loading error: '" + mFile->getFilePath() + "' " + toString(mWidth) + ", " + toString(mHeight) + " : " + toString(channels) + " - " + std::string(SOIL_last_result()) + "\n", Logger::LOG_TYPE_ERROR);*/
				GAE_File_close(texture->file, GAE_FILE_CLOSE_DELETE_DATA, NULL);
				return GAE_FALSE;
			}
			
			retainData ? GAE_File_close(texture->file, GAE_FILE_CLOSE_RETAIN_DATA, &openStatus) : GAE_File_close(texture->file, GAE_FILE_CLOSE_DELETE_DATA, &openStatus);
			if (GAE_FILE_ERROR == openStatus) {
				/*Application::getInstance()->getLogger()->log("Failed to close Texture: " + mFile->getFilePath() + "\n", Logger::LOG_TYPE_ERROR);*/
				return GAE_FALSE;
			}
			break;
		}
		case GAE_TEXTURE_TYPE_BUFFER: {
			platform->texture = loadTextureFromBuffer(texture);

			if (GAE_FALSE == retainData)
				GAE_File_delete(texture->file);

			if (0 == platform->texture) {
				/*Application::getInstance()->getLogger()->log("Texture creation error: " + std::string(SOIL_last_result()) + "\n", Logger::LOG_TYPE_ERROR);*/
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
	SDL_Texture* tex = IMG_LoadTexture_RW(platform->renderer, SDL_RWFromMem((void*)file->buffer, (int)file->bufferSize), 1);
	SDL_QueryTexture(tex, &platform->format, &platform->access, (int*)&texture->width, (int*)&texture->height);

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
			/*Application::getInstance()->getLogger()->log("Invalid Texture Format specified\n", Logger::LOG_TYPE_ERROR);*/
			return tex;
	}
	
	if (imageSize != texture->file->bufferSize) {
		/*Application::getInstance()->getLogger()->log("Expected size of: " + toString(imageSize) + ", buffer size is: " + toString(mFile->getBufferSize()) + "\n", Logger::LOG_TYPE_ERROR);*/
		return tex;
	}
	
	tex = SDL_CreateTexture(platform->renderer, platform->format, platform->access, texture->width, texture->height);
	
	return tex;
}
