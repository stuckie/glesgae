#include "Timer.h"
#include "Clock.h"

#include <stdlib.h>

GAE_Timer_t* GAE_Timer_create(GAE_Clock_t* const clock)
{
	GAE_Timer_t* timer = (GAE_Timer_t*)malloc(sizeof(GAE_Timer_t));
	timer->currentTime = 0.0F;
	timer->deltaTime = 0.0F;
	timer->isPaused = GAE_FALSE;
	timer->lastTime = clock->deltaTime;
	timer->scale = 1.0F;

	return timer;
}

GAE_Timer_t* GAE_Timer_update(GAE_Timer_t* timer, GAE_Clock_t* const clock)
{
	if (GAE_FALSE == timer->isPaused)
		timer->deltaTime = clock->deltaTime - timer->lastTime;
	else
		timer->deltaTime = 0.0F;

	timer->lastTime = clock->deltaTime;
	timer->currentTime += timer->deltaTime  * timer->scale;

	return timer;
}

GAE_Timer_t* GAE_Timer_reset(GAE_Timer_t* timer)
{
	timer->currentTime = 0.0F;
	timer->deltaTime = 0.0F;

	return timer;
}

void GAE_Timer_delete(GAE_Timer_t* timer)
{
	free(timer);
	timer = 0;
}
