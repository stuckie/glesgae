#include "SDL2/SDL.h"

#include "../AudioSystem.h"
#include "../Sound.h"
#include "../../External/mojoAL/AL/al.h"
#include "../../External/mojoAL/AL/alc.h"
#include "../../Utils/Array.h"

typedef struct SDL_AudioSystem_s {
	ALCdevice* device;
	ALCcontext* context;
} SDL_AudioSystem_t;

SDL_AudioSystem_t* createAudioSystem()
{
	SDL_AudioSystem_t* system = malloc(sizeof(SDL_AudioSystem_t));
	system->device = alcOpenDevice(NULL);
	system->context = alcCreateContext(system->device, NULL);
	
	alcMakeContextCurrent(system->context);
	
	return system;
}

GAE_AudioSystem_t* GAE_AudioSystem_create(const unsigned int frequency, const unsigned char channels, const unsigned int samples, const GAE_AudioFormat format)
{
	GAE_AudioSystem_t* audioSystem = malloc(sizeof(GAE_AudioSystem_t));
	audioSystem->frequency = frequency;
	audioSystem->channels = channels;
	audioSystem->samples = samples;
	audioSystem->format = format;
	
	audioSystem->audioSounds = GAE_Array_create(sizeof(GAE_Sound_t));
	audioSystem->platform = createAudioSystem();
	
	return audioSystem;
}

GAE_AudioSystem_t* GAE_AudioSystem_update(GAE_AudioSystem_t* system)
{
	unsigned int i;
	unsigned int total = GAE_Array_length(system->audioSounds);
	
	for (i = 0; i < total; ++i) {
		GAE_Sound_t* sound = GAE_Array_get(system->audioSounds, i);
		GAE_Sound_update(sound);
	}
	
	return system;
}

GAE_AudioSystem_t* GAE_AudioSystem_addSound(GAE_AudioSystem_t* system, struct GAE_Sound_s* sound, unsigned int* outId)
{
	const unsigned int soundsLength = GAE_Array_length(system->audioSounds);
	
	GAE_Array_push(system->audioSounds, sound);
	
	*outId = soundsLength;
	
	return system;
}

GAE_AudioSystem_t* GAE_AudioSystem_getSound(GAE_AudioSystem_t* system, unsigned int id, struct GAE_Sound_s* sound)
{
	sound = GAE_Array_get(system->audioSounds, id);
	return system;
}

GAE_AudioSystem_t* GAE_AudioSystem_removeSound(GAE_AudioSystem_t* system, unsigned int id)
{
	GAE_Sound_t* sound = GAE_Array_get(system->audioSounds, id);
	if (0 != sound) {
		GAE_Sound_destroy(sound);
		GAE_Array_delete(system->audioSounds, id);
	}
	
	return system;
}

void GAE_AudioSystem_destroy(GAE_AudioSystem_t* audioSystem)
{
	SDL_AudioSystem_t* system = audioSystem->platform;
	
	alcMakeContextCurrent(NULL);
	alcDestroyContext(system->context);
	alcCloseDevice(system->device);
}

