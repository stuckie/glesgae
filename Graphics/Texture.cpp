#include "Texture.h"

#include "../External/SOIL/SOIL.h"
#include "../Platform/Application.h"
#include "../Utils/Logger.h"

#if defined(GLX)
	#include "Context/Linux/GLee.h"
#elif defined(WGL)
	#include "Context/Win32/GLee.h"
#elif defined(AGL)
	#include "Context/Darwin/GLee.h"
#elif defined(PANDORA) || defined(ANDROID)
	#if defined(GLES1)
		#include <GLES/gl.h>
	#elif defined(GLES2) || defined(ANDROID)
		#include <GLES2/gl2.h>
	#endif
#endif

using namespace GLESGAE;

Texture::Texture(File* const image)
: mFile(image)
, mId(GL_INVALID_VALUE)
, mWidth()
, mHeight()
, mFormat(FORMAT_INVALID)
, mType(TYPE_FILE)
{
}

Texture::Texture(File* const buffer, const unsigned int width, const unsigned int height)
: mFile(buffer)
, mId(GL_INVALID_VALUE)
, mWidth(width)
, mHeight(height)
, mFormat(FORMAT_INVALID)
, mType(TYPE_BUFFER)
{
}

Texture::Texture(const Texture& texture)
: mFile(texture.mFile)
, mId(texture.mId)
, mWidth(texture.mWidth)
, mHeight(texture.mHeight)
, mFormat(texture.mFormat)
, mType(texture.mType)
{
}

Texture& Texture::operator=(const Texture& texture)
{
	if (this != &texture) {
		mFile = texture.mFile;
		mId = texture.mId;
		mWidth = texture.mWidth;
		mHeight = texture.mHeight;
		mFormat = texture.mFormat;
		mType = texture.mType;
	}
	
	return *this;
}

Texture::~Texture()
{
	kill();
}

void Texture::kill()
{
	if (GL_INVALID_VALUE != mId) {
		glDeleteTextures(1, &mId);
		mId = GL_INVALID_VALUE;
	}
	
	mFile->deleteBuffer();
}

bool Texture::load(const TextureFilter filter, const bool retainData, const TextureFormat format)
{
	if (mId != GL_INVALID_VALUE) {
		Application::getInstance()->getLogger()->log("Texture already loaded: " + mFile->getFilePath() + "\n", Logger::LOG_TYPE_ERROR);
		return false;
	}
	
	switch (mType) {
		case TYPE_FILE: {
			if (0 == mFile->readBuffer()) {
				if (FILEIO::FILE_ERROR == mFile->open(FILEIO::OPEN_READ, FILEIO::FILE_BINARY)) {
					mFile->close(FILEIO::CLOSE_DELETE_DATA);
					Application::getInstance()->getLogger()->log("Failed to open Texture: " + mFile->getFilePath() + "\n", Logger::LOG_TYPE_ERROR);
					return false;
				}
				if (FILEIO::READ_ERROR == mFile->read()) {
					mFile->close(FILEIO::CLOSE_DELETE_DATA);
					Application::getInstance()->getLogger()->log("Failed to read Texture: " + mFile->getFilePath() + "\n", Logger::LOG_TYPE_ERROR);
					return false;
				}
			}
			
			unsigned int flags;
			switch (format) {
				case FORMAT_RGB:
				case FORMAT_RGBA:
					flags = (SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB);
					break;
				case FORMAT_DXT1:
				case FORMAT_DXT5:
					flags = (SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
					break;
				default:
					Application::getInstance()->getLogger()->log("Invalid Texture Format specified\n", Logger::LOG_TYPE_ERROR);
					mFile->close(FILEIO::CLOSE_DELETE_DATA);
					return false;
			}
			
			int width(1);
			int height(1);
			int channels(3);
			GLuint texId(SOIL_load_OGL_texture_from_memory_with_info
				(	mFile->readBuffer()
				,	mFile->getBufferSize()
				,	&width
				,	&height
				,	&channels
				,	0 // use channels from file format
				,	SOIL_CREATE_NEW_ID
				,	flags
				)
			);
			
			mWidth = static_cast<unsigned int>(width);
			mHeight = static_cast<unsigned int>(height);
			
			if (0 == texId) {
				Application::getInstance()->getLogger()->log("Texture loading error: '" + mFile->getFilePath() + "' " + toString(mWidth) + ", " + toString(mHeight) + " : " + toString(channels) + " - " + std::string(SOIL_last_result()) + "\n", Logger::LOG_TYPE_ERROR);
				mFile->close(FILEIO::CLOSE_DELETE_DATA);
				return false;
			}
			else
				mId = texId;
			
			if (FILEIO::FILE_ERROR == (retainData ? mFile->close(FILEIO::CLOSE_RETAIN_DATA) : mFile->close(FILEIO::CLOSE_DELETE_DATA))) {
				Application::getInstance()->getLogger()->log("Failed to close Texture: " + mFile->getFilePath() + "\n", Logger::LOG_TYPE_ERROR);
				return false;
			}
			break;
		}
		case TYPE_BUFFER: {
			unsigned int imageSize(0U);
			unsigned int imageFormat(0U);
			switch (format) {
				case FORMAT_RGB:
					imageSize = mWidth * mHeight * 3;
					imageFormat = 3;
					break;
				case FORMAT_RGBA:
					imageSize = mWidth * mHeight * 4;
					imageFormat = 4;
					break;
				case FORMAT_DXT1:
				case FORMAT_DXT5:
				default:
					Application::getInstance()->getLogger()->log("Invalid Texture Format specified\n", Logger::LOG_TYPE_ERROR);
					return false;
			}
			
			if (imageSize != mFile->getBufferSize()) {
				Application::getInstance()->getLogger()->log("Expected size of: " + toString(imageSize) + ", buffer size is: " + toString(mFile->getBufferSize()) + "\n", Logger::LOG_TYPE_ERROR);
				return false;
			}
			
			GLuint texId(SOIL_create_OGL_texture
				(	mFile->readBuffer()
				,	mWidth
				,	mHeight
				,	imageFormat
				,	SOIL_CREATE_NEW_ID
				,	0
				)
			);
			
			if (false == retainData)
				mFile->deleteBuffer();
			
			if (0 == texId) {
				Application::getInstance()->getLogger()->log("Texture creation error: " + std::string(SOIL_last_result()) + "\n", Logger::LOG_TYPE_ERROR);
				return false;
			}
			else
				mId = texId;
			
			break;
		}
	}
	
	GLint oldId(GL_INVALID_VALUE);
	glGetIntegerv(GL_ACTIVE_TEXTURE, &oldId);
	glActiveTexture(mId);
	switch (filter) {
		case FILTER_NONE:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case FILTER_BILINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case FILTER_TRILINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
	}
	glActiveTexture(oldId);
	return true;
}

bool Texture::save()
{
	return false;
}

