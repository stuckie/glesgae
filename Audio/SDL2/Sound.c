#include "../Sound.h"
#include "../../Buffer/Buffer.h"
#include "../../External/mojoAL/AL/al.h"
#include "../../External/mojoAL/AL/alc.h"
#include "../../External/stb/stb_vorbis.c"
#include <SDL2/SDL.h>

const char* getExtension(const char* const filePath)
{
	const char* dot = &filePath[strlen(filePath)];
	
	while (dot-- > filePath) {
		if (*dot == '.')
			break;
	}

	return dot;
}

/* pinched from mojoAL testposition example */
static ALenum get_openal_format(const SDL_AudioSpec *spec)
{
    if ((spec->channels == 1) && (spec->format == AUDIO_U8)) {
        return AL_FORMAT_MONO8;
    } else if ((spec->channels == 1) && (spec->format == AUDIO_S16SYS)) {
        return AL_FORMAT_MONO16;
    } else if ((spec->channels == 2) && (spec->format == AUDIO_U8)) {
        return AL_FORMAT_STEREO8;
    } else if ((spec->channels == 2) && (spec->format == AUDIO_S16SYS)) {
        return AL_FORMAT_STEREO16;
    } else if ((spec->channels == 1) && (spec->format == AUDIO_F32SYS)) {
        return alIsExtensionPresent("AL_EXT_FLOAT32") ? alGetEnumValue("AL_FORMAT_MONO_FLOAT32") : AL_NONE;
    } else if ((spec->channels == 2) && (spec->format == AUDIO_F32SYS)) {
        return alIsExtensionPresent("AL_EXT_FLOAT32") ? alGetEnumValue("AL_FORMAT_STEREO_FLOAT32") : AL_NONE;
    }
    return AL_NONE;
}

typedef struct PlatformData_s {
	ALuint sourceId;
	ALuint bufferId;
} PlatformData_t;

typedef struct OggPlatformData_s {
	ALuint sourceId;
	ALuint bufferId[2];
	
	stb_vorbis* vorbis;
	ALenum format;
	short** buffers;
	unsigned int bufferCount;
	unsigned int current;
	unsigned int bufferSize;
} OggPlatformData_t;

GAE_Sound_t* GAE_Sound_create(const unsigned int frequency, const unsigned char channels, const unsigned int samples, const GAE_AudioFormat format)
{
	GAE_Sound_t* sound = malloc(sizeof(GAE_Sound_t));
	PlatformData_t* platform = malloc(sizeof(PlatformData_t));

	sound->frequency = frequency;
	sound->channels = channels;
	sound->samples = samples;
	sound->format = format;
	
	sound->data = 0;
	
	alGenSources(1, &platform->sourceId);
	alGenBuffers(1, &platform->bufferId);
	sound->platform = platform;
	
	return sound;
}

void fillOggBuffer(GAE_Sound_t* sound)
{	
	OggPlatformData_t* platform = sound->platform;
	ALuint bufferId;
	ALint processed;
	unsigned int samples;
	
	alGetSourceiv(platform->sourceId, AL_BUFFERS_PROCESSED, &processed);
	if (0 >= processed) return;
	samples = stb_vorbis_get_samples_short_interleaved(platform->vorbis, sound->channels, platform->buffers[platform->current], sound->channels * 4096);
	if (0 == samples && GAE_TRUE == sound->isLooping) {
		stb_vorbis_seek_start(platform->vorbis);
		samples = stb_vorbis_get_samples_short_interleaved(platform->vorbis, sound->channels, platform->buffers[platform->current], sound->channels * 4096);
	} else if (0 == samples && GAE_FALSE == sound->isLooping && 2 == processed) {
		alSourceStop(platform->sourceId);
		sound->fillBuffer = 0;
		return;
	} else if (0 == samples && GAE_FALSE == sound->isLooping && 1 == processed)
		return;
	alSourceUnqueueBuffers(platform->sourceId, 1, &bufferId);
	alBufferData(bufferId, platform->format, platform->buffers[platform->current], sizeof(short) * sound->channels * 4096, sound->frequency);
	alSourceQueueBuffers(platform->sourceId, 1, &bufferId);

	if (++platform->current >= platform->bufferCount) platform->current = 0;
}

GAE_Sound_t* GAE_Sound_createFrom(const char* filePath)
{
	const char* extension = getExtension(filePath);
	GAE_Sound_t* sound = malloc(sizeof(GAE_Sound_t));
	
	if (0 == strcasecmp(".wav", extension)) {
		PlatformData_t* platform = malloc(sizeof(PlatformData_t));
		SDL_AudioSpec spec;
		GAE_BYTE* buf;
		unsigned int buflen;
		ALenum alfmt = AL_NONE;
		
		if (0 != SDL_LoadWAV(filePath, &spec, &buf, &buflen)) {
			alfmt = get_openal_format(&spec);
			alGenSources(1, &platform->sourceId);
			alGenBuffers(1, &platform->bufferId);
			
			alBufferData(platform->bufferId, alfmt, buf, buflen, spec.freq);
		    SDL_FreeWAV(buf);
		    
		    alSourcei(platform->sourceId, AL_BUFFER, platform->bufferId);
    		sound->platform = platform;
		} else {
			free(platform);
			free(sound);
			return 0;
		}
	} else if (0 == strcasecmp(".ogg", extension)) { /* TODO: This is a wee bit nasty and hardcoded */
		int vorbisError;
		OggPlatformData_t* platform = malloc(sizeof(OggPlatformData_t));
		stb_vorbis* vorbis = stb_vorbis_open_filename(filePath, &vorbisError, NULL);
		if (NULL != vorbis) {
			unsigned int buflen;
			ALenum alfmt = AL_NONE;
			stb_vorbis_info info = stb_vorbis_get_info(vorbis);
			unsigned int samples = stb_vorbis_stream_length_in_samples(vorbis);
			if (2 == info.channels) alfmt = AL_FORMAT_STEREO16;
			else alfmt = AL_FORMAT_MONO16;
			
			alGenSources(1, &platform->sourceId);
			alGenBuffers(2, platform->bufferId);
			
			buflen = sizeof(short) * info.channels * 4096;
			
			platform->buffers = malloc(sizeof(short*) * 2);
			platform->buffers[0] = malloc(buflen);
			platform->buffers[1] = malloc(buflen);
			platform->bufferSize = buflen;
			platform->current = 0;
			platform->bufferCount = 2;
			platform->vorbis = vorbis;
			platform->format = alfmt;
			sound->channels = info.channels;
			sound->frequency = info.sample_rate;
			sound->fillBuffer = fillOggBuffer;

			samples = stb_vorbis_get_samples_short_interleaved(vorbis, info.channels, platform->buffers[0], info.channels * 4096);
			alBufferData(platform->bufferId[0], alfmt, platform->buffers[0], sizeof(short) * info.channels * samples, info.sample_rate);
			samples = stb_vorbis_get_samples_short_interleaved(vorbis, info.channels, platform->buffers[1], info.channels * 4096);
			alBufferData(platform->bufferId[1], alfmt, platform->buffers[1], sizeof(short) * info.channels * samples, info.sample_rate);
			
			alSourceQueueBuffers(platform->sourceId, 2, platform->bufferId);
			sound->platform = platform;
		} else {
			free(platform);
			free(sound);
			return 0;
		}
	} else {
		free(sound);
		return 0;
	}
	
	return sound;
}

GAE_Sound_t* GAE_Sound_setLooping(GAE_Sound_t* sound, const GAE_BOOL toLoop)
{
	PlatformData_t* platform = sound->platform;
	
	alSourcei(platform->sourceId, AL_LOOPING, toLoop);
	
	sound->isLooping = toLoop;
	
	return sound;
}

GAE_Sound_t* GAE_Sound_play(GAE_Sound_t* sound)
{
	PlatformData_t* platform = sound->platform;
	
	alSourcePlay(platform->sourceId);
	
	return sound;
}

GAE_Sound_t* GAE_Sound_update(GAE_Sound_t* sound)
{
	if (0 != sound->fillBuffer) (*sound->fillBuffer)(sound);
	
	return sound;
}

void GAE_Sound_destroy(GAE_Sound_t* sound)
{
	PlatformData_t* platform = sound->platform;
	
	alDeleteBuffers(1, &platform->bufferId);
	alDeleteSources(1, &platform->sourceId);
	
	free(sound->platform);
	free(sound);
}

