#include "Timer.h"
#include "Clock.h"

#include <stdlib.h>

GAE_Timer_t* GAE_Timer_create()
{
	GAE_Timer_t* timer = (GAE_Timer_t*)malloc(sizeof(GAE_Timer_t));
	timer->currentTime = 0.0F;
	timer->deltaTime = 0.0F;
	timer->isPaused = GAE_FALSE;
	timer->lastTime = 0.0F;
	timer->scale = 1.0F;

	return timer;
}

GAE_Timer_t* GAE_Timer_update(GAE_Timer_t* timer, GAE_Clock_t* const clock)
{
	const float clockTime = clock->deltaTime * timer->scale;
	if (GAE_FALSE == timer->isPaused)
		timer->deltaTime = clockTime - timer->lastTime;
	else
		timer->deltaTime = 0.0F;

	timer->lastTime = clockTime;
	timer->currentTime += timer->deltaTime;

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
