#include "Buffer.h"

#include <string.h>
#include <stdlib.h>

/* Create a new empty buffer with optional size */
GAE_Buffer_t* GAE_Buffer_create(const unsigned int size)
{
	GAE_Buffer_t* buffer = malloc(sizeof(GAE_Buffer_t));
	
	buffer->data = 0;		
	buffer->length = size;
	buffer->index = 0;
	
	if (0 < size)
		buffer->data = malloc(size);

	return buffer;
}

/* Create a buffer with the given data */
GAE_Buffer_t* GAE_Buffer_createWith(GAE_BYTE* data, const unsigned int size)
{
	GAE_Buffer_t* buffer = malloc(sizeof(GAE_Buffer_t));
	
	buffer->data = data;
	buffer->length = size;
	buffer->index = 0;
	
	return buffer;
}

/* Delete a buffer */
void GAE_Buffer_delete(GAE_Buffer_t* buffer)
{
	if (0 == buffer) return;
	
	free(buffer->data);
	free(buffer);
}

/* Resize the given buffer to the requested size */
GAE_Buffer_t* GAE_Buffer_resize(GAE_Buffer_t* buffer, const unsigned int size)
{
	if (size > buffer->length) {
		GAE_BYTE* data;
		if (0 == buffer->data) { /* don't actually have any data yet... */
			data = malloc(size);
			buffer->data = data;
		} else {
			data = realloc(buffer->data, size);
			if (0 != data) buffer->data = data;
			/* TODO: Deal with error state */
		}
		buffer->length = size;
	}
	/* TODO: support shrinking buffers */
	
	return buffer;
}

/* Seek the index to the given position in the buffer */
GAE_Buffer_t* GAE_Buffer_seek(GAE_Buffer_t* buffer, const unsigned int position)
{
	if (position > buffer->length)
		buffer->index = buffer->length;
	else
		buffer->index = position;
		
	return buffer;
}

/* Clear the Buffer */
GAE_Buffer_t* GAE_Buffer_clear(GAE_Buffer_t* buffer)
{
	memset(buffer->data, 0, buffer->length);
	buffer->index = 0;
	
	return buffer;
}

/* Read x amount of bytes */
GAE_Buffer_t* GAE_Buffer_read(GAE_Buffer_t* buffer, GAE_BYTE* values, const unsigned int amount)
{
	unsigned int index = 0;
	while (index < amount) {
		values[index] = (GAE_BYTE)buffer->data[buffer->index];
		buffer->index = (buffer->index + sizeof(GAE_BYTE)) % buffer->length;
		++index;
	}
	
	return buffer;
}

/* Write x Bytes */
GAE_Buffer_t* GAE_Buffer_write(GAE_Buffer_t* buffer, GAE_BYTE* const values, const unsigned int amount)
{
	unsigned int index = 0;
	while (index < amount) {
		buffer->data[buffer->index] = (GAE_BYTE)values[index];
		buffer->index = (buffer->index + sizeof(GAE_BYTE)) % buffer->length;
		++index;
	}
	
	return buffer;
}

/* Write a string */
GAE_Buffer_t* GAE_Buffer_write_string(GAE_Buffer_t* buffer, const char* const string)
{
	return GAE_Buffer_write(buffer, (GAE_BYTE*)string, strlen(string));
}

