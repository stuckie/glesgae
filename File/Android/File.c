#include "../File.h"

#include <SDL2/SDL.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <android/log.h>
	#define ANDROID_INFO(...) ((void)__android_log_print(ANDROID_LOG_INFO, "[FILE] ", __VA_ARGS__))

AAssetManager* getAssetManager(void);

GAE_File_t* GAE_File_create(const char* filePath) {
	GAE_File_t* file = malloc(sizeof(GAE_File_t));
	GAE_PlatformFile_t* platform = malloc(sizeof(GAE_PlatformFile_t));

	strncpy(file->filePath, filePath, sizeof(file->filePath));
	file->buffer = 0;
	file->readPosition = 0U;
	file->bufferSize = 0U;
	file->fileSize = 0U;
	file->fileStatus = GAE_FILE_CLOSED;
	file->openMode = GAE_FILE_OPEN_READ;
	file->owned = GAE_FALSE;
	platform->file = 0;
	platform->asset = 0;
	file->platformFile = (void*)platform;

	return file;
}

void GAE_File_delete(GAE_File_t* file) {
	GAE_PlatformFile_t* platform = (GAE_PlatformFile_t*)file->platformFile;
	if (0 != platform->file) {
		fclose(platform->file);
		platform->file = 0;
	}

	if (0 != platform->asset) {
		AAsset_close(platform->asset);
		platform->asset = 0;
	}

	free(platform);
	free(file);
	file = 0;
}

GAE_File_t* GAE_File_open(GAE_File_t* file, const GAE_FILE_OPEN_MODE openMode, const GAE_FILE_MODE fileMode, GAE_FILE_STATUS* status) {
	GAE_PlatformFile_t* platform = (GAE_PlatformFile_t*)file->platformFile;
	char options[2];

	if (file->fileStatus != GAE_FILE_CLOSED) {
		if (0 != status)
			*status = GAE_FILE_ERROR;
		return file;
	}
	
	if (0 != platform->file) {
		if (0 != status)
			*status = GAE_FILE_ERROR;
		return file;
	}
	
	if (0 != file->buffer) {
		if (0 != status)
			*status = GAE_FILE_ERROR;
		return file;
	}
	
	switch (openMode) {
		case GAE_FILE_OPEN_READ:
			options[0] = 'r';
			file->owned = GAE_TRUE;
			break;
		case GAE_FILE_OPEN_WRITE:
			options[0] = 'w';
			file->owned = GAE_FALSE;
			break;
		case GAE_FILE_OPEN_APPEND:
			options[0] = 'a';
			file->owned = GAE_FALSE;
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
	
	platform->file = fopen(file->filePath, options);
	
	if (0 == platform->file) /* not on sdcard, lets try the apk */
		platform->asset = AAssetManager_open(getAssetManager(), file->filePath, AASSET_MODE_UNKNOWN);

	if ((0 == platform->file) && (0 == platform->asset)) { /* nope, not found at all */
		if (0 != status)
			*status = GAE_FILE_NOT_FOUND;
		ANDROID_INFO("File Not Found: %s", file->filePath);
		return file;
	}
	
	file->fileStatus = GAE_FILE_OPEN;
	file->openMode = openMode;

	if (0 != platform->file) {	
		fseek(platform->file, 0, SEEK_END);
		file->fileSize = ftell(platform->file);
		rewind(platform->file);
	}
	else
		file->fileSize = AAsset_getLength(platform->asset);
	
	if (0 != status)
		*status = file->fileStatus;

	ANDROID_INFO("Found: %s of size %d", file->filePath, (unsigned int)file->fileSize);

	return file;
}

GAE_File_t* GAE_File_close(GAE_File_t* file, const GAE_FILE_CLOSE_MODE mode, GAE_FILE_STATUS* status) {
	GAE_PlatformFile_t* platform = (GAE_PlatformFile_t*)file->platformFile;

	if (file->fileStatus != GAE_FILE_OPEN) {
		if (0 != status)
			*status = GAE_FILE_ERROR;
		return file;
	}
	
	if (0 == platform->file) {
		if (0 != status)
			*status = GAE_FILE_ERROR;
		return file;
	}
	
	if (0 != platform->file) {
		fclose(platform->file);
		platform->file = 0;
	}

	if (0 != platform->asset) {
		AAsset_close(platform->asset);
		platform->asset = 0;
	}
	
	file->fileStatus = GAE_FILE_CLOSED;
	if (0 != status)
		*status = file->fileStatus;
	
	if (mode == GAE_FILE_CLOSE_DELETE_DATA) {
		if (GAE_TRUE == file->owned) {
			free(file->buffer);
			file->buffer = 0;
			file->owned = GAE_FALSE;
			file->bufferSize = 0U;
		}
	}
	
	return file;
}

GAE_File_t* GAE_File_deleteBuffer(GAE_File_t* file, GAE_BOOL* status) {
	if (0 == file->buffer) {
		if (0 != status)
			*status = GAE_FALSE;
		return file;
	}
	
	if (GAE_FALSE == file->owned) {
		if (0 != status)
			*status = GAE_FALSE;
		return file;
	}
	
	free(file->buffer);
	file->buffer = 0;

	if (0 != status)
		*status = GAE_TRUE;

	return file;
}

GAE_File_t* GAE_File_read(GAE_File_t* file, const unsigned long amount, GAE_FILE_READ_STATUS* status) {
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
	
	if (0 == platform->file && 0 == platform->asset) {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
	
	if (GAE_FALSE == file->owned) {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
	
	if (readAmount < file->fileSize)
		file->bufferSize = readAmount;
	else {
		file->bufferSize = file->fileSize;
		readAmount = file->fileSize;
	}
	
	if (0 != file->buffer)
		free(file->buffer);
	
	file->buffer = malloc(file->bufferSize + 1U);
	memset(file->buffer, '\0', file->bufferSize);
	if (0 == file->buffer) {
		if (0 != status)
			*status = GAE_FILE_READ_ERROR;
		return file;
	}
	
	file->owned = GAE_TRUE;

	if (0 != platform->file)
		read = fread(file->buffer, 1, file->bufferSize, platform->file);
	if (0 != platform->asset)
		read = AAsset_read(platform->asset, file->buffer, file->bufferSize);

	file->readPosition += (unsigned long)read;

	ANDROID_INFO("Read %d", file->readPosition);
	
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

GAE_File_t* GAE_File_write(GAE_File_t* file, GAE_FILE_WRITE_STATUS* status) {
	GAE_PlatformFile_t* platform = (GAE_PlatformFile_t*)file->platformFile;
	long written = 0;

	if ((file->openMode != GAE_FILE_OPEN_WRITE) && (file->openMode != GAE_FILE_OPEN_APPEND)) {
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
	
	if (0 == file->buffer) {
		if (0 != status)
			*status = GAE_FILE_WRITE_ERROR;
		return file;
	}
	
	written = fwrite(file->buffer, 1, file->bufferSize, platform->file);
	if ((unsigned long)(written) == file->bufferSize) {
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

GAE_File_t* GAE_FILE_setReadPosition(GAE_File_t* file, const unsigned long readPosition, GAE_FILE_READ_STATUS* status) {
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
	
	if (file->readPosition < file->fileSize) {
		file->readPosition = readPosition;
		if (0 != platform->file)
			fseek(platform->file, file->readPosition, SEEK_SET);
		if (0 != platform->asset)
			AAsset_seek(platform->asset, file->readPosition, SEEK_SET);
		if (0 != status)
			*status = GAE_FILE_READ_OK;
		return file;
	}
	else {
		file->readPosition = file->fileSize;
		if (0 != platform->file)
			fseek(platform->file, 0, SEEK_END);
		if (0 != platform->asset)
			AAsset_seek(platform->asset, 0, SEEK_END);
		if (0 != status)
			*status = GAE_FILE_READ_EOF;
		return file;
	}
}

GAE_File_t* GAE_File_setBuffer(GAE_File_t* file, unsigned char* buffer, const unsigned long size, const GAE_FILE_BUFFER_TYPE type, GAE_BOOL* status) {
	if (file->fileStatus == GAE_FILE_OPEN) {
		if (0 != status)
			*status = GAE_FALSE;
		return file;
	}
	
	if (file->owned == GAE_TRUE)
		free(file->buffer);
	
	switch(type) {
		case GAE_FILE_BUFFER_COPY: {
			file->buffer = malloc(size);
			if (0 == file->buffer) {
				if (0 != status)
					*status = GAE_FALSE;
				return file;
			}
			memcpy(file->buffer, buffer, size);
			file->owned = GAE_TRUE;
			file->bufferSize = size;
			file->readPosition = 0U;
		}
		break;
		case GAE_FILE_BUFFER_NOT_OWNED: {
			file->buffer = buffer;
			file->owned = GAE_FALSE;
			file->bufferSize = size;
			file->readPosition = 0U;
		}
		break;
		case GAE_FILE_BUFFER_OWNED: {
			file->buffer = buffer;
			file->owned = GAE_TRUE;
			file->bufferSize = size;
			file->readPosition = 0U;
		}
		break;
	}
	
	if (0 != status)
		*status = GAE_TRUE;
	return file;
}

GAE_File_t* GAE_FILE_newBuffer(GAE_File_t* file, const unsigned long size, GAE_BOOL* status) {
	if (file->fileStatus == GAE_FILE_OPEN) {
		if (0 != status)
			*status = GAE_FALSE;
		return file;
	}
	
	if (file->owned == GAE_TRUE)
		free(file->buffer);
	
	file->buffer = malloc(size);
	file->owned = GAE_TRUE;
	file->bufferSize = size;
	file->readPosition = 0U;
	
	if (0 != status)
		*status = GAE_TRUE;
	return file;
}

AAssetManager* getAssetManager(void) {
	JNIEnv* jniEnv = (JNIEnv*)SDL_AndroidGetJNIEnv();

	jclass sdlClass = (*jniEnv)->FindClass(jniEnv, "org/libsdl/app/SDLActivity");
	if (sdlClass == 0) {
		ANDROID_INFO("Cannot find SDLClass");
		assert(0);
		return NULL;
	}

	jmethodID mid = (*jniEnv)->GetStaticMethodID(jniEnv, sdlClass, "getContext","()Landroid/content/Context;");
	jobject context = (*jniEnv)->CallStaticObjectMethod(jniEnv, sdlClass, mid);
	if (context == 0) {
		ANDROID_INFO("Cannot find Context");
		return NULL;
	}

	mid = (*jniEnv)->GetMethodID(jniEnv, (*jniEnv)->GetObjectClass(jniEnv, context), "getAssets", "()Landroid/content/res/AssetManager;");
	jobject assets = (*jniEnv)->CallObjectMethod(jniEnv, context, mid);
	if (assets == 0) {
		ANDROID_INFO("Cannot find AssetManager");
		return NULL;
	}

	ANDROID_INFO("Found AssetManager");
	return AAssetManager_fromJava(jniEnv, assets);
}

