#ifndef _AUDIO_SYSTEM_H_
#define _AUDIO_SYSTEM_H_

typedef enum GAE_AudioFormat_e
{	GAE_AudioFormat_s8
,	GAE_AudioFormat_u8
,	GAE_AudioFormat_s16
,	GAE_AudioFormat_u16
,	GAE_AudioFormat_s32
,	GAE_AudioFormat_u32
,	GAE_AudioFormat_f32
} GAE_AudioFormat;

struct GAE_Array_s;
struct GAE_Sound_s;

typedef struct GAE_AudioSystem_s {
	unsigned int frequency;
	unsigned char channels;
	unsigned int samples;
	GAE_AudioFormat format;
	
	struct GAE_Array_s* audioSounds;
	
	void* platform;
} GAE_AudioSystem_t;

/* Create a new Audio System */
GAE_AudioSystem_t* GAE_AudioSystem_create(const unsigned int frequency, const unsigned char channels, const unsigned int samples, const GAE_AudioFormat format);

/* Update the given Audio System */
GAE_AudioSystem_t* GAE_AudioSystem_update(GAE_AudioSystem_t* system);

/* Add a sound to the Audio System, returning the id in outId */
GAE_AudioSystem_t* GAE_AudioSystem_addSound(GAE_AudioSystem_t* system, struct GAE_Sound_s* sound, unsigned int* outId);

/* Get a sound via it's id */
GAE_AudioSystem_t* GAE_AudioSystem_getSound(GAE_AudioSystem_t* system, unsigned int id, struct GAE_Sound_s* sound);

/* Remove a sound from the Audio System */
GAE_AudioSystem_t* GAE_AudioSystem_removeSound(GAE_AudioSystem_t* system, unsigned int id);

/* Destroys the given audio system */
void GAE_AudioSystem_destroy(GAE_AudioSystem_t* audioSystem);


#endif

