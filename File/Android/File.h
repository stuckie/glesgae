#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>

struct AAsset;

typedef struct GAE_PlatformFile_s {
	FILE* file;
	struct AAsset* asset;
} GAE_PlatformFile_t;

static const unsigned int GAE_FILE_READ_ALL = (unsigned int)-1;

GAE_File_t* GAE_File_create(const char* filePath);
void GAE_File_delete(GAE_File_t* file);
GAE_File_t* GAE_File_open(GAE_File_t* file, const GAE_FILE_OPEN_MODE openMode, const GAE_FILE_MODE fileMode, GAE_FILE_STATUS* status);
GAE_File_t* GAE_File_close(GAE_File_t* file, const GAE_FILE_CLOSE_MODE closeMode, GAE_FILE_STATUS* status);
GAE_File_t* GAE_File_deleteBuffer(GAE_File_t* file, GAE_BOOL* success);
GAE_File_t* GAE_File_read(GAE_File_t* file, const unsigned long amount, GAE_FILE_READ_STATUS* status);
GAE_File_t* GAE_File_write(GAE_File_t* file, GAE_FILE_WRITE_STATUS* status);
GAE_File_t* GAE_File_setReadPosition(GAE_File_t* file, const unsigned long position, GAE_FILE_READ_STATUS* status);
GAE_File_t* GAE_File_setBuffer(GAE_File_t* file, GAE_BYTE* buffer, const unsigned long size, const GAE_FILE_BUFFER_TYPE type, GAE_BOOL* success);
GAE_File_t* GAE_File_newBuffer(GAE_File_t* file, const unsigned long size, GAE_BOOL* success);

#endif
