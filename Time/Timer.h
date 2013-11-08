#ifndef _TIMER_H_
#define _TIMER_H_

#include "../GAE_Types.h"

struct GAE_Clock_s;

typedef struct GAE_Timer_s {
	float lastTime;
	float currentTime;
	float deltaTime;
	float scale;
	GAE_BOOL isPaused;
} GAE_Timer_t;

GAE_Timer_t* GAE_Timer_reset(GAE_Timer_t* timer);
GAE_Timer_t* GAE_Timer_update(GAE_Timer_t* timer, struct GAE_Clock_s* const clock);

#endif

