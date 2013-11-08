#include "Timer.h"
#include "Clock.h"

GAE_Timer_t* GAE_Timer_update(GAE_Timer_t* timer, GAE_Clock_t* const clock) {
	const float clockTime = clock->deltaTime * timer->scale;
	if (GAE_FALSE == timer->isPaused)
		timer->deltaTime = clockTime - timer->lastTime;
	else
		timer->deltaTime = 0.0F;

	timer->lastTime = clockTime;
	timer->currentTime += timer->deltaTime;

	return timer;
}

GAE_Timer_t* GAE_Timer_reset(GAE_Timer_t* timer) {
	timer->currentTime = 0.0F;
	timer->deltaTime = 0.0F;

	return timer;
}
