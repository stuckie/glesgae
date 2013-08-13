#include "IndexBuffer.h"

#include <cstring> // for memcpy
#if defined(GLX)
	#include "Context/Linux/GLee.h"
#elif defined(GLES1)
	#if defined(PANDORA) || defined(ANDROID)
		#include <GLES/gl.h>
	#endif
#elif defined(GLES2)
	#if defined(PANDORA) || defined(ANDROID)
		#include <GLES2/gl2.h>
	#endif
#endif

using namespace GLESGAE;

IndexBuffer::IndexBuffer(unsigned char* const data, const unsigned int count, const IndexType type, const FormatType format, const DrawType drawType)
: mCount(count)
, mSize(count)
, mData(0)
, mVboId(0)
, mFormat(format)
, mType(type)
, mDrawType(drawType)
, mUpdateData(0)
{
	switch (type) {
		case INDEX_FLOAT:
			mSize = count * sizeof(float);
			break;
		case INDEX_UNSIGNED_BYTE:
			mSize = count * sizeof(unsigned char);
			break;
		case INDEX_UNSIGNED_SHORT:
			mSize = count * sizeof(unsigned short);
			break;
		default:
			break;
	};
	mData = new unsigned char[mSize];
	std::memcpy(mData, data, mSize);
}

IndexBuffer::IndexBuffer(const IndexBuffer& indexBuffer)
: mCount(indexBuffer.mCount)
, mSize(indexBuffer.mSize)
, mData(indexBuffer.mData)
, mVboId(indexBuffer.mVboId)
, mFormat(indexBuffer.mFormat)
, mType(indexBuffer.mType)
, mDrawType(indexBuffer.mDrawType)
, mUpdateData(0)
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
		mDrawType = indexBuffer.mDrawType;
		mUpdateData = indexBuffer.mUpdateData;
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
	if (0 != mUpdateData) {
		delete mUpdateData->data;
		delete mUpdateData;
	}
}

