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

typedef enum GAE_FILE_BUFFER_TYPE_e {
	GAE_FILE_BUFFER_COPY
,	GAE_FILE_BUFFER_OWNED
,	GAE_FILE_BUFFER_NOT_OWNED
} GAE_FILE_BUFFER_TYPE;

typedef enum GAE_FILE_WRITE_STATUS_e {
	GAE_FILE_WRITE_OK
,	GAE_FILE_WRITE_ERROR
} GAE_FILE_WRITE_STATUS;

typedef enum GAE_FILE_CLOSE_MODE_e {
	GAE_FILE_CLOSE_RETAIN_DATA
,	GAE_FILE_CLOSE_DELETE_DATA
} GAE_FILE_CLOSE_MODE;

typedef struct GAE_File_s {
	char filePath[1024];
	GAE_BYTE* buffer;
	unsigned long readPosition;
	unsigned long bufferSize;
	unsigned long fileSize;
	GAE_FILE_STATUS fileStatus;
	GAE_FILE_OPEN_MODE openMode;
	GAE_BOOL owned;
	void* platformFile;
} GAE_File_t;

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
