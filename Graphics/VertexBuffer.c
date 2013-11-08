#include "VertexBuffer.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#if defined(LINUX)
	#include "Context/GLX/GLee.h"
#elif defined(WIN32)
	#include "Context/Win32/GLee.h"
#elif defined(GLES1)
	#if defined(PANDORA) || defined(ANDROID)
		#include <GLES/gl.h>
	#endif
#elif defined(GLES2)
	#if defined(PANDORA) || defined(ANDROID)
		#include <GLES2/gl2.h>
	#endif
#endif

GAE_VertexBuffer_Format_t GAE_VertexBuffer_Format_create(const GAE_VertexBuffer_FormatType type, unsigned int offset) {
	GAE_VertexBuffer_Format_t format;
	format.type = type;
	format.offset = offset;

	switch (type) {
		case GAE_VERTEXBUFFER_FORMAT_CUSTOM_2F:
		case GAE_VERTEXBUFFER_FORMAT_POSITION_2F:
		case GAE_VERTEXBUFFER_FORMAT_TEXTURE_2F:
			format.size = sizeof(float) * 2;
			break;
		case GAE_VERTEXBUFFER_FORMAT_CUSTOM_3F:
		case GAE_VERTEXBUFFER_FORMAT_POSITION_3F:
		case GAE_VERTEXBUFFER_FORMAT_NORMAL_3F:
		case GAE_VERTEXBUFFER_FORMAT_COLOUR_3F:
		case GAE_VERTEXBUFFER_FORMAT_TEXTURE_3F:
			format.size = sizeof(float) * 3;
			break;
		case GAE_VERTEXBUFFER_FORMAT_CUSTOM_4F:
		case GAE_VERTEXBUFFER_FORMAT_POSITION_4F:
		case GAE_VERTEXBUFFER_FORMAT_COLOUR_4F:
		case GAE_VERTEXBUFFER_FORMAT_TEXTURE_4F:
			format.size = sizeof(float) * 4;
			break;
		case GAE_VERTEXBUFFER_FORMAT_CUSTOM_2B:
		case GAE_VERTEXBUFFER_FORMAT_POSITION_2B:
		case GAE_VERTEXBUFFER_FORMAT_TEXTURE_2B:
			format.size = sizeof(char) * 2;
			break;
		case GAE_VERTEXBUFFER_FORMAT_CUSTOM_3B:
		case GAE_VERTEXBUFFER_FORMAT_POSITION_3B:
		case GAE_VERTEXBUFFER_FORMAT_NORMAL_3B:
		case GAE_VERTEXBUFFER_FORMAT_COLOUR_3UB:
		case GAE_VERTEXBUFFER_FORMAT_TEXTURE_3B:
			format.size = sizeof(char) * 3;
			break;
		case GAE_VERTEXBUFFER_FORMAT_CUSTOM_4B:
		case GAE_VERTEXBUFFER_FORMAT_POSITION_4B:
		case GAE_VERTEXBUFFER_FORMAT_COLOUR_4UB:
		case GAE_VERTEXBUFFER_FORMAT_TEXTURE_4B:
			format.size = sizeof(char) * 4;
		case GAE_VERTEXBUFFER_FORMAT_CUSTOM_2S:
		case GAE_VERTEXBUFFER_FORMAT_POSITION_2S:
		case GAE_VERTEXBUFFER_FORMAT_TEXTURE_2S:
			format.size = sizeof(short) * 2;
			break;
		case GAE_VERTEXBUFFER_FORMAT_CUSTOM_3S:
		case GAE_VERTEXBUFFER_FORMAT_POSITION_3S:
		case GAE_VERTEXBUFFER_FORMAT_NORMAL_3S:
		case GAE_VERTEXBUFFER_FORMAT_COLOUR_3S:
		case GAE_VERTEXBUFFER_FORMAT_TEXTURE_3S:
			format.size = sizeof(short) * 3;
			break;
		case GAE_VERTEXBUFFER_FORMAT_CUSTOM_4S:
		case GAE_VERTEXBUFFER_FORMAT_POSITION_4S:
		case GAE_VERTEXBUFFER_FORMAT_COLOUR_4S:
		case GAE_VERTEXBUFFER_FORMAT_TEXTURE_4S:
			format.size = sizeof(short) * 4;
			break;
		default:
			break;
	};

	return format;
}

GAE_VertexBuffer_t* GAE_VertexBuffer_create(GAE_BYTE* const data, const unsigned int size, const GAE_VertexBuffer_Type type) {
	GAE_VertexBuffer_t* buffer = (GAE_VertexBuffer_t*)malloc(sizeof(GAE_VertexBuffer_t));
	GAE_VertexBuffer_Format_t invalidFormat;
	unsigned int index = 0U;
	
	invalidFormat.type = GAE_VERTEXBUFFER_INVALID_FORMAT;
	invalidFormat.size = 0;
	invalidFormat.offset = 0;

	for (index = 0U; index < GAE_VERTEXBUFFER_FORMAT_SIZE; ++index)
		buffer->format[index] = invalidFormat;

	buffer->size = size;
	buffer->data = malloc(size);
	buffer->stride = 0U;
	buffer->offset = 0U;
	buffer->type = type;
	buffer->vboId = 0;
	buffer->updateData = 0;
	

	memcpy(buffer->data, data, size);
	return buffer;
}

GAE_VertexBuffer_t* GAE_VertexBuffer_createWithFormat(GAE_BYTE* const data, const unsigned int size, const GAE_VertexBuffer_Type type, const GAE_VertexBuffer_Format_t format[]) {
	GAE_VertexBuffer_t* buffer = GAE_VertexBuffer_create(data, size, type);
	unsigned int index = 0U;

	for (index = 0U; index < GAE_VERTEXBUFFER_FORMAT_SIZE; ++index) {
		buffer->stride += format[index].size;
		buffer->format[index] = format[index];
	}

	return buffer;
}

GAE_VertexBuffer_t* GAE_VertexBuffer_clone(GAE_VertexBuffer_t* buffer) {
	GAE_VertexBuffer_t* newBuffer = GAE_VertexBuffer_createWithFormat(buffer->data, buffer->size, buffer->type, buffer->format);
	newBuffer->vboId = 0;
	newBuffer->updateData = 0;

	return newBuffer;
}

void GAE_VertexBuffer_delete(GAE_VertexBuffer_t* buffer) {
	if (0 != buffer->data) {
		free(buffer->data);
		buffer->data = 0;
	}

	if (0 != buffer->updateData) {
		if (0 != buffer->updateData->data) {
			free(buffer->updateData->data);
			buffer->updateData->data = 0;
		}
		free(buffer->updateData);
		buffer->updateData = 0;
	}

	if (0 != buffer->vboId) {
		glDeleteBuffers(1, buffer->vboId);
		free(buffer->vboId);
		buffer->vboId = 0;
	}

	free(buffer);
	buffer = 0;
}

GAE_VertexBuffer_t* GAE_VertexBuffer_setInterleaved(GAE_VertexBuffer_t* buffer) {
	unsigned int vertexSize = 0U;
	unsigned int index = 0U;

	unsigned int identifiers = 0U;
	for (identifiers = 0U; identifiers < GAE_VERTEXBUFFER_FORMAT_SIZE; ++identifiers) {
		if (GAE_VERTEXBUFFER_INVALID_FORMAT == buffer->format[identifiers].type)
			break; /* We now know the size of the active formats in this buffer */
	}

	for (index = 0U; index < identifiers; ++index)
		vertexSize += buffer->format[index].size;
	
	buffer->stride = vertexSize;
	
	/* Remap offsets due to interleaved stride */
	for (index = 0U; index < identifiers; ++index)
		buffer->format[index] = GAE_VertexBuffer_Format_create(buffer->format[index].type, buffer->format[index].size);

	return buffer;
}

GAE_VertexBuffer_t* GAE_VertexBuffer_addFormatIdentifier(GAE_VertexBuffer_t* buffer, const GAE_VertexBuffer_FormatType type, const unsigned int amount) {
	unsigned int index = 0U;
	GAE_VertexBuffer_Format_t newFormat;
	for (index = 0U; index < GAE_VERTEXBUFFER_FORMAT_SIZE; ++index) {
		if (GAE_VERTEXBUFFER_INVALID_FORMAT == buffer->format[index].type) {
			newFormat = GAE_VertexBuffer_Format_create(type, buffer->offset);
			buffer->offset += newFormat.size * amount;
			buffer->format[index] = newFormat;
			return buffer;
		}
	}

	assert(0); /* no space for the format identifier */
	return buffer;
}
