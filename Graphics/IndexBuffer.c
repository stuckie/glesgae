#include "IndexBuffer.h"

#include <string.h>
#include <stdlib.h>

#if defined(LINUX)
	#include "Context/GLX/GLee.h"
#elif defined(GLES1)
	#if defined(PANDORA) || defined(ANDROID)
		#include <GLES/gl.h>
	#endif
#elif defined(GLES2)
	#if defined(PANDORA) || defined(ANDROID)
		#include <GLES2/gl2.h>
	#endif
#endif

GAE_IndexBuffer_t* GAE_IndexBuffer_create(GAE_BYTE* const data, const unsigned int count, const GAE_IndexBuffer_IndexType type, const GAE_IndexBuffer_Format format, const GAE_IndexBuffer_Draw drawType) {
	GAE_IndexBuffer_t* buffer = malloc(sizeof(GAE_IndexBuffer_t));
	buffer->count = count;
	buffer->size = count;
	buffer->format = format;
	buffer->type = type;
	buffer->draw = drawType;
	buffer->updateData = 0;
	buffer->vboId = 0;

	switch (type) {
		case GAE_INDEXBUFFER_INDEX_FLOAT:
			buffer->size = count * sizeof(float);
			break;
		case GAE_INDEXBUFFER_INDEX_UNSIGNED_BYTE:
			buffer->size = count * sizeof(unsigned char);
			break;
		case GAE_INDEXBUFFER_INDEX_UNSIGNED_SHORT:
			buffer->size = count * sizeof(unsigned short);
			break;
		default:
			break;
	};

	buffer->data = malloc(buffer->size);
	memcpy(buffer->data, data, buffer->size);

	return buffer;
}

GAE_IndexBuffer_t* GAE_IndexBuffer_clone(GAE_IndexBuffer_t* const buffer) {
	GAE_IndexBuffer_t* newBuffer = malloc(sizeof(GAE_IndexBuffer_t));
	newBuffer->count = buffer->count;
	newBuffer->size = buffer->size;
	newBuffer->format = buffer->format;
	newBuffer->type = buffer->type;
	newBuffer->draw = buffer->draw;
	newBuffer->updateData = 0;
	newBuffer->vboId = 0;

	newBuffer->data = malloc(newBuffer->size);
	memcpy(newBuffer->data, buffer->data, newBuffer->size);

	return newBuffer;
}

void GAE_IndexBuffer_delete(GAE_IndexBuffer_t* buffer) {
	if (0 != buffer->data) {
		free(buffer->data);
		buffer->data = 0;
	}

	if (0 != buffer->vboId) {
		glDeleteBuffers(1, buffer->vboId);
		free(buffer->vboId);
		buffer->vboId = 0;
	}

	if (0 != buffer->updateData) {
		if (0 != buffer->updateData->data) {
			free(buffer->updateData->data);
			buffer->updateData->data = 0;
		}
		free(buffer->updateData);
		buffer->updateData = 0;
	}

	free(buffer);
	buffer = 0;
}
