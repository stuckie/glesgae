#include "IndexBuffer.h"

#include <cstring> // for memcpy
#if defined(GLX)
	#include "Context/Linux/GLee.h"
#elif defined(GLES1)
	#if defined(PANDORA)
		#include <GLES/gl.h>
	#endif
#elif defined(GLES2)
	#if defined(PANDORA)
		#include <GLES2/gl2.h>
	#endif
#endif

using namespace GLESGAE;

IndexBuffer::IndexBuffer(unsigned char* const data, const unsigned int size, const IndexType type, const FormatType format)
: mSize(size)
, mData(new unsigned char[size])
, mVboId(0)
, mFormat(format)
, mType(type)
{
	std::memcpy(mData, data, size);
}

IndexBuffer::IndexBuffer(const IndexBuffer& indexBuffer)
: mSize(indexBuffer.mSize)
, mData(indexBuffer.mData)
, mVboId(indexBuffer.mVboId)
, mFormat(indexBuffer.mFormat)
, mType(indexBuffer.mType)
{
}

IndexBuffer& IndexBuffer::operator=(const IndexBuffer& indexBuffer)
{
	if (this != &indexBuffer) {
		mSize = indexBuffer.mSize;
		mData = indexBuffer.mData;
		mVboId = indexBuffer.mVboId;
		mFormat = indexBuffer.mFormat;
		mType = indexBuffer.mType;
	}
	
	return *this;
}

IndexBuffer::~IndexBuffer()
{
	if (0 != mData) {
		delete[] mData;
		mData = 0;
	}
	if (0 != mVboId) {
		glDeleteBuffers(1, mVboId);
		mVboId = 0;
	}
}

