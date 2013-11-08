#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "../GAE_Types.h"

typedef struct GAE_Clock_s {
	float deltaTime;
	float currentTime;
	GAE_BOOL isPaused;
	void* platformData;
} GAE_Clock_t;

GAE_Clock_t* GAE_Clock_create(void);
GAE_Clock_t* GAE_Clock_reset(GAE_Clock_t* clock);
GAE_Clock_t* GAE_Clock_update(GAE_Clock_t* clock);
GAE_Clock_t* GAE_Clock_pause(GAE_Clock_t* clock);
GAE_Clock_t* GAE_Clock_resume(GAE_Clock_t* clock);
void GAE_Clock_delete(GAE_Clock_t* clock);

#endif

