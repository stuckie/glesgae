#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_

#include "../GAE_Types.h"

typedef struct GAE_IndexBuffer_UpdateData_s	{
	GAE_BOOL retain;
	unsigned int offset;
	unsigned int size;
	GAE_BYTE* data;
} GAE_IndexBuffer_UpdateData_t;
			
typedef enum GAE_IndexBuffer_Draw_e {
	GAE_INDEXBUFFER_DRAW_STATIC
,	GAE_INDEXBUFFER_DRAW_STREAM
,	GAE_INDEXBUFFER_DRAW_DYNAMIC
} GAE_IndexBuffer_Draw;
			
typedef enum GAE_IndexBuffer_IndexType_e {
	GAE_INDEXBUFFER_INDEX_FLOAT					/* unsupported by ES 1 */
,	GAE_INDEXBUFFER_INDEX_UNSIGNED_BYTE
,	GAE_INDEXBUFFER_INDEX_UNSIGNED_SHORT
,	GAE_INDEXBUFFER_INDEX_UNSIGNED_INT			/* unsupported by unextended ES variants. */
} GAE_IndexBuffer_IndexType;
			
typedef enum GAE_IndexBuffer_Format_e {
	GAE_INDEXBUFFER_FORMAT_POINTS
,	GAE_INDEXBUFFER_FORMAT_LINES
,	GAE_INDEXBUFFER_FORMAT_LINE_STRIP
,	GAE_INDEXBUFFER_FORMAT_LINE_LOOP
,	GAE_INDEXBUFFER_FORMAT_TRIANGLES
,	GAE_INDEXBUFFER_FORMAT_TRAINGLE_STRIP
,	GAE_INDEXBUFFER_FORMAT_TRIANGLE_FAN
} GAE_IndexBuffer_Format;

typedef struct GAE_IndexBuffer_s {
	unsigned int count;
	unsigned int size;
	GAE_BYTE* data;
	unsigned int* vboId;
	GAE_IndexBuffer_Format format;
	GAE_IndexBuffer_IndexType type;
	GAE_IndexBuffer_Draw draw;
	GAE_IndexBuffer_UpdateData_t* updateData;
} GAE_IndexBuffer_t;

GAE_IndexBuffer_t* GAE_IndexBuffer_create(GAE_BYTE* const data, const unsigned int count, const GAE_IndexBuffer_IndexType type, const GAE_IndexBuffer_Format format, const GAE_IndexBuffer_Draw drawType);
GAE_IndexBuffer_t* GAE_IndexBuffer_clone(GAE_IndexBuffer_t* const buffer);
void GAE_IndexBuffer_delete(GAE_IndexBuffer_t* buffer);

#endif
