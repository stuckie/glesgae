#include "VertexBuffer.h"

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

VertexBuffer::VertexBuffer(unsigned char* const data, const unsigned int size, const Format format[], const BufferType bufferType)
: mSize(size)
, mData(new unsigned char[size])
, mStride(0U)
, mOffset(0U)
, mType(bufferType)
, mVboId(0)
, mFormat()
, mUpdateData(0)
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
, mOffset(0U)
, mType(bufferType)
, mVboId(0)
, mFormat()
, mUpdateData(0)
{
	std::memcpy(mData, data, size);
}

VertexBuffer::VertexBuffer(const VertexBuffer& vertexBuffer)
: mSize(vertexBuffer.mSize)
, mData(vertexBuffer.mData)
, mStride(vertexBuffer.mStride)
, mOffset(vertexBuffer.mOffset)
, mType(vertexBuffer.mType)
, mVboId(vertexBuffer.mVboId)
, mFormat()
, mUpdateData(vertexBuffer.mUpdateData)
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
		mOffset = vertexBuffer.mOffset;
		mType = vertexBuffer.mType;
		mVboId = vertexBuffer.mVboId;
		mUpdateData = vertexBuffer.mUpdateData;
		
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
	
	if (0 != mUpdateData) {
		delete mUpdateData->data;
		delete mUpdateData;
	}
}

unsigned char* VertexBuffer::getWriteableData()
{
	if (0 != mVboId) { // force a new buffer to be made - this one is dirty.
		// This is very expensive... should use glMapBuffer instead, but not all platforms support it.
		// Try the updateData method instead as it will call glBufferSubData in the renderer to update it.
		glDeleteBuffers(1, mVboId);
		mVboId = 0;
	}
	
	return mData;
}

void VertexBuffer::addFormatIdentifier(const FormatType formatType, const unsigned int amount)
{
	for (unsigned int index(0U); index < FORMAT_SIZE; ++index) {
		if (INVALID_FORMAT == mFormat[index].getType()) {
			Format newFormat(formatType, mOffset);
			mOffset += newFormat.getSize() * amount;
			mFormat[index] = newFormat;
			return;
		}
	}
	
	//! TODO: OOPS! No more space left! Assert! Break! ACHTUNG!
}

void VertexBuffer::isInterleaved()
{
	// Need to work out how many active format identifiers we have
	unsigned int identifiers(0U);
	for (identifiers = 0U; identifiers < FORMAT_SIZE; ++identifiers) {
		if (INVALID_FORMAT == mFormat[identifiers].getType())
			break;
	}

	// Work out size of a vertex.
	unsigned int vertexSize(0U);
	for (unsigned int index(0U); index < identifiers; ++index)
		vertexSize += mFormat[index].getSize();
	
	mStride = vertexSize;
	
	// Remap offsets
	for (unsigned int index(0U); index < identifiers; ++index)
		mFormat[index] = Format(mFormat[index].getType(), mFormat[index].getSize());
}
