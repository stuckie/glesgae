#ifndef _SOUND_H_
#define _SOUND_H_

#include "AudioSystem.h"
#include "../GAE_Types.h"

typedef void(*GAE_Sound_fillBuffer)(struct GAE_Sound_s* sound);

typedef struct GAE_Sound_s {
	unsigned int frequency;
	unsigned char channels;
	unsigned int samples;
	GAE_AudioFormat format;
	GAE_BOOL isLooping;
	GAE_BOOL isStream;
	GAE_Sound_fillBuffer fillBuffer;
	
	struct GAE_Buffer_s* data;
	void* platform;
} GAE_Sound_t;

GAE_Sound_t* GAE_Sound_create(const unsigned int frequency, const unsigned char channels, const unsigned int samples, const GAE_AudioFormat format);

GAE_Sound_t* GAE_Sound_createFrom(const char* filePath);

GAE_Sound_t* GAE_Sound_update(GAE_Sound_t* sound);

GAE_Sound_t* GAE_Sound_setLooping(GAE_Sound_t* sound, const GAE_BOOL toLoop);

GAE_Sound_t* GAE_Sound_play(GAE_Sound_t* sound);

void GAE_Sound_destroy(GAE_Sound_t* sound);

#endif

