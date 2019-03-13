#include "../File.h"

#include "../../Buffer/Buffer.h"

#include <string.h>
#include <stdlib.h>

GAE_File_t* GAE_File_create(const char* const filePath, const GAE_FILE_OPEN_MODE openMode, const GAE_FILE_MODE fileMode, GAE_FILE_STATUS* status) {
	GAE_File_t* file = malloc(sizeof(GAE_File_t));
	GAE_PlatformFile_t* platform = malloc(sizeof(GAE_PlatformFile_t));
	char options[2];

	file->readPosition = 0U;
	file->fileSize = 0U;
	file->fileStatus = GAE_FILE_CLOSED;
	file->openMode = openMode;
	file->fileMode = fileMode;	

	platform->file = 0;
	file->platformFile = (void*)platform;
	
	switch (openMode) {
		case GAE_FILE_OPEN_READ:
			options[0] = 'r';
			break;
		case GAE_FILE_OPEN_WRITE:
			options[0] = 'w';
			break;
		case GAE_FILE_OPEN_APPEND:
			options[0] = 'a';
			break;
	};
	
	switch (fileMode) {
		case GAE_FILE_ASCII:
			options[1] = '\0';
			break;
		case GAE_FILE_BINARY:
			options[1] = 'b';
			break;
	};
	
	platform->file = fopen(filePath, options);
	
	if (0 == platform->file) {
		if (0 != status)
			*status = GAE_FILE_NOT_FOUND;
		return file;
	}
	
	file->fileStatus = GAE_FILE_OPEN;
	
	fseek(platform->file, 0, SEEK_END);
	file->fileSize = ftell(platform->file);
	rewind(platform->file);
	
	if (0 != status)
		*status = file->fileStatus;

	return file;
}

void GAE_File_delete(GAE_File_t* file) {
	GAE_PlatformFile_t* platform = (GAE_PlatformFile_t*)file->platformFile;

	if ((file->fileStatus == GAE_FILE_OPEN)
	&& (0 != platform->file))
		fclose(platform->file);

	free(platform);
	free(file);
}

GAE_File_t* GAE_File_read(GAE_File_t* file, GAE_Buffer_t* buffer, const unsigned long amount, GAE_FILE_READ_STATUS* status) {
	GAE_PlatformFile_t* platform = (GAE_PlatformFile_t*)file->platformFile;
	unsigned long readAmount = amount;
	long read = 0;

	if (file->openMode != GAE_FILE_OPEN_READ) {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
	
	if (file->fileStatus != GAE_FILE_OPEN) {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
	
	if (0 == platform->file) {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
	
	if (0 == buffer) {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
	
	if (readAmount > file->fileSize)
		readAmount = file->fileSize;
	
	if (buffer->length < buffer->index + readAmount)
		GAE_Buffer_resize(buffer, buffer->index + readAmount);
		
	read = fread((void*)(buffer->data + buffer->index), 1, readAmount, platform->file);
	file->readPosition += (unsigned long)read;
	buffer->index += (unsigned int)read;
	
	if ((unsigned long)(read) == readAmount) {
		if (0 != status)
			*status = GAE_FILE_READ_OK;
		return file;
	}
	else if (feof(platform->file)) {
		if (0 != status)
			*status = GAE_FILE_READ_EOF;
		return file;
	}
	else {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
}

GAE_File_t* GAE_File_write(GAE_File_t* file, GAE_Buffer_t* const buffer, GAE_FILE_WRITE_STATUS* status) {
	GAE_PlatformFile_t* platform = (GAE_PlatformFile_t*)file->platformFile;
	long written = 0;

	if ((file->openMode != GAE_FILE_OPEN_WRITE) 
	&& (file->openMode != GAE_FILE_OPEN_APPEND)) {
		if (0 != status)
			*status = GAE_FILE_WRITE_ERROR;
		return file;
	}
	
	if (file->fileStatus != GAE_FILE_OPEN) {
		if (0 != status)
			*status = GAE_FILE_WRITE_ERROR;
		return file;
	}
	
	if (0 == platform->file) {
		if (0 != status)
			*status = GAE_FILE_WRITE_ERROR;
		return file;
	}
	
	if (0 == buffer) {
		if (0 != status)
			*status = GAE_FILE_WRITE_ERROR;
		return file;
	}
	
	written = fwrite(buffer->data, 1, buffer->length, platform->file);
	fflush(platform->file);
	if ((unsigned long)(written) == buffer->length) {
		if (0 != status)
			*status = GAE_FILE_WRITE_OK;
		return file;
	}
	else {
		if (0 != status)
			*status = GAE_FILE_WRITE_ERROR;
		return file;
	}
}

GAE_File_t* GAE_FILE_seek(GAE_File_t* file, const unsigned long position, GAE_FILE_READ_STATUS* status) {
	GAE_PlatformFile_t* platform = (GAE_PlatformFile_t*)file->platformFile;

	if (file->fileStatus != GAE_FILE_OPEN) {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
	
	if (file->openMode != GAE_FILE_OPEN_READ) {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
	
	if (0 == platform->file) {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
	
	if (position < file->fileSize) {
		file->readPosition = position;
		fseek(platform->file, file->readPosition, SEEK_SET);
		if (0 != status)
			*status = GAE_FILE_READ_OK;
		return file;
	}
	else {
		file->readPosition = file->fileSize;
		fseek(platform->file, 0, SEEK_END);
		if (0 != status)
			*status = GAE_FILE_READ_EOF;
		return file;
	}
}

