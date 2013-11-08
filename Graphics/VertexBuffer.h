#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

#include "../GAE_Types.h"

#define GAE_VERTEXBUFFER_FORMAT_SIZE 8U

typedef struct GAE_VertexBuffer_UpdateData_s {
	GAE_BOOL retain;
	unsigned int offset;
	unsigned int size;
	GAE_BYTE* data;
} GAE_VertexBuffer_UpdateData_t;

typedef enum GAE_VertexBuffer_Type_e {
	GAE_VERTEXBUFFER_TYPE_STATIC
,	GAE_VERTEXBUFFER_TYPE_DYNAMIC
,	GAE_VERTEXBUFFER_TYPE_STREAM
} GAE_VertexBuffer_Type;

typedef enum GAE_VertexBuffer_FormatType_e {
	GAE_VERTEXBUFFER_INVALID_FORMAT
	/* Float*/
,	GAE_VERTEXBUFFER_FORMAT_CUSTOM_4F
,	GAE_VERTEXBUFFER_FORMAT_CUSTOM_3F
,	GAE_VERTEXBUFFER_FORMAT_CUSTOM_2F
,	GAE_VERTEXBUFFER_FORMAT_POSITION_2F
,	GAE_VERTEXBUFFER_FORMAT_POSITION_3F
,	GAE_VERTEXBUFFER_FORMAT_POSITION_4F
,	GAE_VERTEXBUFFER_FORMAT_NORMAL_3F
,	GAE_VERTEXBUFFER_FORMAT_COLOUR_3F	/* Not available in GLES1*/
,	GAE_VERTEXBUFFER_FORMAT_COLOUR_4F
,	GAE_VERTEXBUFFER_FORMAT_TEXTURE_2F
,	GAE_VERTEXBUFFER_FORMAT_TEXTURE_3F
,	GAE_VERTEXBUFFER_FORMAT_TEXTURE_4F
	/* Unsigned/Byte*/
,	GAE_VERTEXBUFFER_FORMAT_CUSTOM_2B
,	GAE_VERTEXBUFFER_FORMAT_CUSTOM_3B
,	GAE_VERTEXBUFFER_FORMAT_CUSTOM_4B
,	GAE_VERTEXBUFFER_FORMAT_POSITION_2B
,	GAE_VERTEXBUFFER_FORMAT_POSITION_3B
,	GAE_VERTEXBUFFER_FORMAT_POSITION_4B
,	GAE_VERTEXBUFFER_FORMAT_NORMAL_3B
,	GAE_VERTEXBUFFER_FORMAT_COLOUR_3UB	/* Not available in GLES1*/
,	GAE_VERTEXBUFFER_FORMAT_COLOUR_4UB
,	GAE_VERTEXBUFFER_FORMAT_TEXTURE_2B
,	GAE_VERTEXBUFFER_FORMAT_TEXTURE_3B
,	GAE_VERTEXBUFFER_FORMAT_TEXTURE_4B
	/* Short*/
,	GAE_VERTEXBUFFER_FORMAT_CUSTOM_2S
,	GAE_VERTEXBUFFER_FORMAT_CUSTOM_3S
,	GAE_VERTEXBUFFER_FORMAT_CUSTOM_4S
,	GAE_VERTEXBUFFER_FORMAT_POSITION_2S
,	GAE_VERTEXBUFFER_FORMAT_POSITION_3S
,	GAE_VERTEXBUFFER_FORMAT_POSITION_4S
,	GAE_VERTEXBUFFER_FORMAT_NORMAL_3S
,	GAE_VERTEXBUFFER_FORMAT_COLOUR_3S	/* Not available in GLES1*/
,	GAE_VERTEXBUFFER_FORMAT_COLOUR_4S	/* Not available in GLES1*/
,	GAE_VERTEXBUFFER_FORMAT_TEXTURE_2S
,	GAE_VERTEXBUFFER_FORMAT_TEXTURE_3S
,	GAE_VERTEXBUFFER_FORMAT_TEXTURE_4S
} GAE_VertexBuffer_FormatType;

typedef struct GAE_VertexBuffer_Format_s {
	GAE_VertexBuffer_FormatType type;
	unsigned int size;
	unsigned int offset;
} GAE_VertexBuffer_Format_t;

typedef struct GAE_VertexBuffer_s {
	unsigned int size;
	GAE_BYTE* data;
	unsigned int stride;
	unsigned int offset;
	unsigned int* vboId;
	GAE_VertexBuffer_Type type;
	GAE_VertexBuffer_Format_t format[GAE_VERTEXBUFFER_FORMAT_SIZE];
	GAE_VertexBuffer_UpdateData_t* updateData;
} GAE_VertexBuffer_t;

GAE_VertexBuffer_Format_t GAE_VertexBuffer_Format_create(const GAE_VertexBuffer_FormatType type, unsigned int offset);

GAE_VertexBuffer_t* GAE_VertexBuffer_create(GAE_BYTE* const data, const unsigned int size, const GAE_VertexBuffer_Type type);
GAE_VertexBuffer_t* GAE_VertexBuffer_createWithFormat(GAE_BYTE* const data, const unsigned int size, const GAE_VertexBuffer_Type type, const GAE_VertexBuffer_Format_t format[]);
GAE_VertexBuffer_t* GAE_VertexBuffer_clone(GAE_VertexBuffer_t* buffer);
void GAE_VertexBuffer_delete(GAE_VertexBuffer_t* buffer);

GAE_VertexBuffer_t* GAE_VertexBuffer_setInterleaved(GAE_VertexBuffer_t* buffer);
GAE_VertexBuffer_t* GAE_VertexBuffer_addFormatIdentifier(GAE_VertexBuffer_t* buffer, const GAE_VertexBuffer_FormatType type, const unsigned int amount);

#endif
