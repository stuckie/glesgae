#include "Texture.h"

#include <cstdio>
#if defined(GLX)
	#include "Context/Linux/GLee.h"
#elif defined(PANDORA)
	#if defined(GLES1)
		#include <GLES/gl.h>
	#elif defined(GLES2)
		#include <GLES2/gl2.h>
	#endif
#endif

using namespace GLESGAE;

Texture::~Texture()
{
	if (0 != mData) {
		delete[] mData;
		mData = 0;
		
		if (static_cast<unsigned int>(-1) != mId) {
			glDeleteTextures(1, &mId);
			mId = static_cast<unsigned int>(-1);
		}
	}
}

void Texture::loadBMP(const std::string& fileName)
{
	FILE *file;
	unsigned long size(0UL);		// size of the image in bytes.
	unsigned short int planes(0U);	// number of planes in image (must be 1) 
	unsigned short int bpp(0U);		// number of bits per pixel (must be 24)

	// make sure the file is there.
	if ((file = fopen(fileName.c_str(), "rb"))==NULL)
		return;

	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	if (1 != fread(&mWidth, 4, 1, file))
		return;

	// read the height 
	if (1 != fread(&mHeight, 4, 1, file))
		return;

	// read the planes
	if (1 != fread(&planes, 2, 1, file))
		return;

	if (1 != planes) // Only supporting single layer BMP just now
		return;

	// read the bpp
	if (1 != fread(&bpp, 2, 1, file))
		return;

	if (24 == bpp) {
		size = mWidth * mHeight * 3U; // RGB
		mType = RGB;
	}
	else if (32 == bpp) {
		size = mWidth * mHeight * 4U; // RGBA
		mType = RGBA;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	// read the data. 
	mData = new unsigned char[size];
	if (mData == 0)
		return;	

	if (1 != fread(mData, size, 1, file))
		return;

	if (24 == bpp) {
		for (unsigned int index(0U); index < size; index += 3U) { // reverse all of the colors. (bgr -> rgb)
			unsigned char temp(mData[index]);
			mData[index] = mData[index + 2U];
			mData[index + 2U] = temp;
		}
	}
	else if (32 == bpp) {
		for (unsigned int index(0U); index < size; index += 4U) { // reverse all of the colors. (bgra -> rgba)
			unsigned char temp(mData[index]);
			mData[index] = mData[index + 2U];
			mData[index + 2U] = temp;
		}
	}

	createGLid();

	delete [] mData;
	mData = 0;
}

void Texture::createGLid()
{
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);
	
	// Enable some filtering - we want pixels in this case!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	// Load up our data into the texture reference
	switch (mType) {
		case RGB:
			glTexImage2D(GL_TEXTURE_2D, 0U, GL_RGB, mWidth, mHeight, 0U, GL_RGB, GL_UNSIGNED_BYTE, mData);
			break;
		case RGBA:
			glTexImage2D(GL_TEXTURE_2D, 0U, GL_RGBA, mWidth, mHeight, 0U, GL_RGBA, GL_UNSIGNED_BYTE, mData);
			break;
		case INVALID_FORMAT:
		default:
			break;
	};
}

