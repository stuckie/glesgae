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

VertexBuffer::VertexBuffer(unsigned char* const data, const unsigned int size, const std::vector<Format>& format)
: mData(new unsigned char[size])
, mSize(size)
, mStride(0U)
, mVboId(0U)
, mFormat(format)
{
	std::memcpy(mData, data, size);

	for (std::vector<Format>::const_iterator itr(mFormat.begin()); itr < mFormat.end(); ++itr)
		mStride += itr->getSize();
		
	glGenBuffers(1U, &mVboId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);
	glBufferData(GL_ARRAY_BUFFER, mSize, mData, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(unsigned char* const data, const unsigned int size)
: mData(new unsigned char[size])
, mSize(size)
, mStride(0U)
, mVboId(0U)
, mFormat()
{
	std::memcpy(mData, data, size);
	
	glGenBuffers(1U, &mVboId);
	glBindBuffer(GL_ARRAY_BUFFER, mVboId);
	glBufferData(GL_ARRAY_BUFFER, mSize, mData, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const VertexBuffer& vertexBuffer)
: mData(vertexBuffer.mData)
, mSize(vertexBuffer.mSize)
, mStride(vertexBuffer.mStride)
, mVboId(vertexBuffer.mVboId)
, mFormat(vertexBuffer.mFormat)
{
}

void VertexBuffer::addFormatIdentifier(const FormatType formatType, const unsigned int amount)
{
	Format newFormat(formatType, mStride);
	mStride += newFormat.getSize() * amount;
	mFormat.push_back(newFormat);
}

