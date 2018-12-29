#include "../../Texture.h"

#include <stdlib.h>

#include "../../../Utils/HashString.h"
#include "../../../External/stb/stb_image.h"
#include "../../../File/File.h"

#if defined(GLX)
	#include "../../Context/GLX/GLee.h"
#elif defined(WGL)
	#include "../../Context/Win32/GLee.h"
#elif defined(AGL)
	#include "../../Context/Darwin/GLee.h"
#elif defined(PANDORA) || defined(ANDROID)
	#if defined(GLES1)
		#include <GLES/gl.h>
	#elif defined(GLES2) || defined(ANDROID)
		#include <GLES2/gl2.h>
	#endif
#endif

static GLuint loadTextureFromFile(GAE_Texture_t* texture);
static GLuint loadTextureFromBuffer(GAE_Texture_t* texture);

GAE_Texture_t* GAE_Texture_createFromFile(GAE_File_t* const image) {
	GAE_Texture_t* texture = malloc(sizeof(GAE_Texture_t));
	GAE_GL_Texture_t* platform = malloc(sizeof(GAE_GL_Texture_t));

	texture->file = image;
	texture->width = 0U;
	texture->height = 0U;
	texture->type = GAE_TEXTURE_TYPE_FILE;

	platform->id = GL_INVALID_VALUE;
	platform->format = GAE_GL_TEXTURE_FORMAT_INVALID;
	platform->filter = GAE_GL_TEXTURE_FILTER_NONE;

	texture->platform = (void*)platform;

	return texture;
}

GAE_Texture_t* GAE_Texture_createFromBuffer(GAE_File_t* const buffer, const unsigned int width, const unsigned int height) {
	GAE_Texture_t* texture = malloc(sizeof(GAE_Texture_t));
	GAE_GL_Texture_t* platform = malloc(sizeof(GAE_GL_Texture_t));

	texture->file = buffer;
	texture->width = width;
	texture->height = height;
	texture->type = GAE_TEXTURE_TYPE_BUFFER;

	platform->id = GL_INVALID_VALUE;
	platform->format = GAE_GL_TEXTURE_FORMAT_INVALID;
	platform->filter = GAE_GL_TEXTURE_FILTER_NONE;

	texture->platform = (void*)platform;

	return texture;
}

void GAE_Texture_delete(GAE_Texture_t* texture) {
	GAE_GL_Texture_t* platform = (GAE_GL_Texture_t*)texture->platform;

	if (GL_INVALID_VALUE != platform->id) {
		glDeleteTextures(1, &platform->id);
		platform->id = GL_INVALID_VALUE;
	}

	GAE_File_delete(texture->file);
	free(platform);
	free(texture);
	texture = 0;
}

GAE_BOOL GAE_Texture_load(GAE_Texture_t* texture, const GAE_BOOL retainData) {
	GAE_GL_Texture_t* platform = (GAE_GL_Texture_t*)texture->platform;

	GAE_File_t* file = texture->file;
	GAE_FILE_STATUS openStatus;
	GAE_FILE_READ_STATUS readStatus;

	if (GL_INVALID_VALUE != platform->id) {
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

			platform->id = loadTextureFromFile(texture);

			if (GL_INVALID_VALUE == platform->id) {
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
			platform->id = loadTextureFromBuffer(texture);

			if (GAE_FALSE == retainData)
				GAE_File_delete(texture->file);

			if (GL_INVALID_VALUE == platform->id) {
				/*Application::getInstance()->getLogger()->log("Texture creation error: " + std::string(SOIL_last_result()) + "\n", Logger::LOG_TYPE_ERROR);*/
				return GAE_FALSE;
			}

			break;
		}
	}
	
	switch (platform->filter) {
		case GAE_GL_TEXTURE_FILTER_NONE:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case GAE_GL_TEXTURE_FILTER_BILINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case GAE_GL_TEXTURE_FILTER_TRILINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	return GAE_TRUE;
}

/* todo: unimplemented */
GAE_BOOL GAE_Texture_save(GAE_Texture_t* texture) {
	GAE_UNUSED(texture);
	return GAE_FALSE;
}

GLuint loadTextureFromFile(GAE_Texture_t* texture) {
	GAE_GL_Texture_t* platform = (GAE_GL_Texture_t*)texture->platform;
	GAE_File_t* file = texture->file;

	int width = 1;
	int height = 1;
	int channels = 3;
	GLuint texId = GL_INVALID_VALUE;

	switch (platform->format) {
		case GAE_GL_TEXTURE_FORMAT_RGB:
			channels = 3;
			break;
		case GAE_GL_TEXTURE_FORMAT_RGBA:
			channels = 4;
			break;
		case GAE_GL_TEXTURE_FORMAT_DXT1:
		case GAE_GL_TEXTURE_FORMAT_DXT5:
		default:
			/*Application::getInstance()->getLogger()->log("Invalid Texture Format specified\n", Logger::LOG_TYPE_ERROR);*/
			return texId;
	}
	
    int nFormat = STBI_rgb_alpha;
    unsigned char* data = stbi_load_from_memory(file->buffer, file->bufferSize, &width, &height, &nFormat, channels);
	
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, (3 == nFormat) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	texture->width = (unsigned int)width;
	texture->height = (unsigned int)height;

	return texId;
}

GLuint loadTextureFromBuffer(GAE_Texture_t* texture) {
	GAE_GL_Texture_t* platform = (GAE_GL_Texture_t*)texture->platform;
	unsigned int imageSize = 0U;
	unsigned int imageFormat = 0U;
	GLuint texId = GL_INVALID_VALUE;

	switch (platform->format) {
		case GAE_GL_TEXTURE_FORMAT_RGB:
			imageSize = texture->width * texture->height * 3;
			imageFormat = 3;
			break;
		case GAE_GL_TEXTURE_FORMAT_RGBA:
			imageSize = texture->width * texture->height * 4;
			imageFormat = 4;
			break;
		case GAE_GL_TEXTURE_FORMAT_DXT1:
		case GAE_GL_TEXTURE_FORMAT_DXT5:
		default:
			/*Application::getInstance()->getLogger()->log("Invalid Texture Format specified\n", Logger::LOG_TYPE_ERROR);*/
			return texId;
	}
	
	if (imageSize != texture->file->bufferSize) {
		/*Application::getInstance()->getLogger()->log("Expected size of: " + toString(imageSize) + ", buffer size is: " + toString(mFile->getBufferSize()) + "\n", Logger::LOG_TYPE_ERROR);*/
		return texId;
	}
	
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, (3 == imageFormat) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, texture->file->buffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	return texId;
}
