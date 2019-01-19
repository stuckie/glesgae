#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>

struct AAsset;

typedef struct GAE_PlatformFile_s {
	FILE* file;
	struct AAsset* asset;
} GAE_PlatformFile_t;

#endif
