#include "VertexBuffer.h"

#include <cstring> // for memcpy
#if defined(GLX)
	#include "GLee.h"
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
, mVboId(GL_INVALID_VALUE)
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
, mVboId(GL_INVALID_VALUE)
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
, mFormat(vertexBuffer.mFormat)
{
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

