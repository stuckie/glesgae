#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "../GAE_Types.h"

typedef struct GAE_Buffer_s {
	GAE_BYTE* data;
	unsigned int length;
	unsigned int index;
} GAE_Buffer_t;

#define GAE_BUFFER_BEGIN 0
#define GAE_BUFFER_END (unsigned int)-1
#define GAE_BUFFER_MAX_STRING 4096

/* Create a new empty buffer with given size */
GAE_Buffer_t* GAE_Buffer_create(const unsigned int size);

/* Delete a buffer */
void GAE_Buffer_delete(GAE_Buffer_t* buffer);

/* Resize the given buffer to the requested size */
GAE_Buffer_t* GAE_Buffer_resize(GAE_Buffer_t* buffer, const unsigned int size);

/* Seek the index to the given position in the buffer */
GAE_Buffer_t* GAE_Buffer_seek(GAE_Buffer_t* buffer, const unsigned int position);

/* Clear the buffer */
GAE_Buffer_t* GAE_Buffer_clear(GAE_Buffer_t* buffer);

/* **** Read Interface **** */
GAE_Buffer_t* GAE_Buffer_read(GAE_Buffer_t* buffer, GAE_BYTE* values, const unsigned int amount);

#define GAE_Buffer_read_byte(buffer, value) GAE_Buffer_read(buffer, value, 1)
#define GAE_Buffer_read_bytes(buffer, value, amount) GAE_Buffer_read(buffer, value, amount)
#define GAE_Buffer_read_char(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(char))
#define GAE_Buffer_read_chars(buffer, value, amount) GAE_Buffer_read(buffer, (GAE_BYTE*)value, amount * sizeof(char))
#define GAE_Buffer_read_int8(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(int8_t))
#define GAE_Buffer_read_int16(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(int16_t))
#define GAE_Buffer_read_int32(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(int32_t))
#define GAE_Buffer_read_int64(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(int64_t))
#define GAE_Buffer_read_uint8(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(uint8_t))
#define GAE_Buffer_read_uint16(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(uint16_t))
#define GAE_Buffer_read_uint32(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(uint32_t))
#define GAE_Buffer_read_uint64(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(uint64_t))
#define GAE_Buffer_read_float(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(float))
#define GAE_Buffer_read_double(buffer, value) GAE_Buffer_read(buffer, (GAE_BYTE*)value, sizeof(double))

/* **** Write Interface **** */
GAE_Buffer_t* GAE_Buffer_write(GAE_Buffer_t* buffer, GAE_BYTE* const values, const unsigned int amount);
GAE_Buffer_t* GAE_Buffer_write_string(GAE_Buffer_t* buffer, const char* const string);

#define GAE_Buffer_write_byte(buffer, value) GAE_Buffer_write(buffer, value, 1)
#define GAE_Buffer_write_bytes(buffer, value, amount) GAE_Buffer_writr(buffer, value, amount)
#define GAE_Buffer_write_char(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(char))
#define GAE_Buffer_write_chars(buffer, value, amount) GAE_Buffer_write(buffer, (GAE_BYTE*)value, amount * sizeof(char))
#define GAE_Buffer_write_int8(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(int8_t))
#define GAE_Buffer_write_int16(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(int16_t))
#define GAE_Buffer_write_int32(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(int32_t))
#define GAE_Buffer_write_int64(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(int64_t))
#define GAE_Buffer_write_uint8(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(uint8_t))
#define GAE_Buffer_write_uint16(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(uint16_t))
#define GAE_Buffer_write_uint32(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(uint32_t))
#define GAE_Buffer_write_uint64(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(uint64_t))
#define GAE_Buffer_write_float(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(float))
#define GAE_Buffer_write_double(buffer, value) GAE_Buffer_write(buffer, (GAE_BYTE*)value, sizeof(double))

#endif

