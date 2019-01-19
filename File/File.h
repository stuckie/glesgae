#ifndef _BASE_FILE_H_
#define _BASE_FILE_H_

#include "../GAE_Types.h"

typedef enum GAE_FILE_OPEN_MODE_e {
	GAE_FILE_OPEN_READ
,	GAE_FILE_OPEN_WRITE
,	GAE_FILE_OPEN_APPEND
} GAE_FILE_OPEN_MODE;
	
typedef enum GAE_FILE_MODE_e {
	GAE_FILE_ASCII
,	GAE_FILE_BINARY
} GAE_FILE_MODE;

typedef enum GAE_FILE_STATUS_e {
	GAE_FILE_ERROR
,	GAE_FILE_OPEN
,	GAE_FILE_CLOSED
,	GAE_FILE_EOF
,	GAE_FILE_NOT_FOUND
} GAE_FILE_STATUS;

typedef enum GAE_FILE_READ_STATUS_e {
	GAE_FILE_READ_OK
,	GAE_FILE_READ_ERROR
,	GAE_FILE_READ_EOF
} GAE_FILE_READ_STATUS;

typedef enum GAE_FILE_WRITE_STATUS_e {
	GAE_FILE_WRITE_OK
,	GAE_FILE_WRITE_ERROR
} GAE_FILE_WRITE_STATUS;

typedef struct GAE_File_s {
	unsigned long readPosition;
	unsigned long fileSize;
	
	GAE_FILE_OPEN_MODE openMode;
	GAE_FILE_STATUS fileStatus;
	GAE_FILE_MODE fileMode;
	
	void* platformFile;
} GAE_File_t;

struct GAE_Buffer_s;

static const unsigned int GAE_FILE_READ_ALL = (unsigned int)-1;

/* Create a new File construct */
GAE_File_t* GAE_File_create(const char* const filePath, const GAE_FILE_OPEN_MODE openMode, const GAE_FILE_MODE fileMode, GAE_FILE_STATUS* status);

/* Delete a File construct */
void GAE_File_delete(GAE_File_t* file);

/* Read into a Buffer the specified amount */
GAE_File_t* GAE_File_read(GAE_File_t* file, struct GAE_Buffer_s* buffer, const unsigned long amount, GAE_FILE_READ_STATUS* status);

/* Write to file the specified Buffer */
GAE_File_t* GAE_File_write(GAE_File_t* file, struct GAE_Buffer_s* const buffer, GAE_FILE_WRITE_STATUS* status);

/* Seek the position */
GAE_File_t* GAE_File_seek(GAE_File_t* file, const unsigned long position, GAE_FILE_READ_STATUS* status);

#endif

#if defined(LINUX) || defined(PANDORA)
#include "Linux/File.h"
#elif defined(WIN32)
#include "Win32/File.h"
#elif defined(ANDROID)
#include "Android/File.h"
#elif defined(IOS) || defined(OSX)
#include "Mac/File.h"
#endif
