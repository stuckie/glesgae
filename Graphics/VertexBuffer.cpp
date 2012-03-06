#include "VertexBuffer.h"

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

VertexBuffer::VertexBuffer(unsigned char* const data, const unsigned int size, const Format format[], const BufferType bufferType)
: mSize(size)
, mData(new unsigned char[size])
, mStride(0U)
, mType(bufferType)
, mVboId(0)
, mFormat()
{
	std::memcpy(mData, data, size);

	for (unsigned int index(0U); index < FORMAT_SIZE; ++index) {
		mStride += format[index].getSize();
		mFormat[index] = format[index];
	}
}

VertexBuffer::VertexBuffer(unsigned char* const data, const unsigned int size, const BufferType bufferType)
: mSize(size)
, mData(new unsigned char[size])
, mStride(0U)
, mType(bufferType)
, mVboId(0)
, mFormat()
{
	std::memcpy(mData, data, size);
}

VertexBuffer::VertexBuffer(const VertexBuffer& vertexBuffer)
: mSize(vertexBuffer.mSize)
, mData(vertexBuffer.mData)
, mStride(vertexBuffer.mStride)
, mType(vertexBuffer.mType)
, mVboId(vertexBuffer.mVboId)
, mFormat()
{
	for (unsigned int index(0U); index < FORMAT_SIZE; ++index)
		mFormat[index] = vertexBuffer.mFormat[index];
}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& vertexBuffer)
{
	if (this != &vertexBuffer) {
		mSize = vertexBuffer.mSize;
		mData = vertexBuffer.mData;
		mStride = vertexBuffer.mStride;
		mType = vertexBuffer.mType;
		mVboId = vertexBuffer.mVboId;
		
		for (unsigned int index(0U); index < FORMAT_SIZE; ++index)
			mFormat[index] = vertexBuffer.mFormat[index];
	}
	
	return *this;
}

VertexBuffer::~VertexBuffer()
{
	if (0 != mVboId) {
		glDeleteBuffers(1, mVboId);
		mVboId = 0;
	}
	
	if (0 != mData) {	
		delete [] mData;
		mData = 0;
	}
}

void VertexBuffer::addFormatIdentifier(const FormatType formatType, const unsigned int amount)
{
	for (unsigned int index(0U); index < FORMAT_SIZE; ++index) {
		if (INVALID_FORMAT == mFormat[index].getType()) {
			Format newFormat(formatType, mStride);
			mStride += newFormat.getSize() * amount;
			mFormat[index] = newFormat;
			return;
		}
	}
	
	//! TODO: OOPS! No more space left! Assert! Break! ACHTUNG!
}

