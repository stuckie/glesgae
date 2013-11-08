#include "../Clock.h"

#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif

#include <stdlib.h>
#include <time.h>

typedef struct GAE_Clock_Linux_s {
	double startTime;
	double currentTime;
	double currentDelta;
	double pausedTime;
} GAE_Clock_Linux_t;

double getCurrentTime(const struct timespec* time);

GAE_Clock_t* GAE_Clock_create(void) {
	GAE_Clock_t* clock = malloc(sizeof(GAE_Clock_t));
	GAE_Clock_Linux_t* linuxClock = malloc(sizeof(GAE_Clock_Linux_t));
	struct timespec time;

	clock->deltaTime = 0.0F;
	clock->currentTime = 0.0F;
	clock->isPaused = GAE_FALSE;
	clock->platformData = linuxClock;

	clock_gettime(CLOCK_MONOTONIC, &time);
	linuxClock->startTime = getCurrentTime(&time);
	linuxClock->currentTime = linuxClock->startTime;
	linuxClock->currentDelta = 0.0;
	linuxClock->pausedTime = 0.0;


	return clock;
}

void GAE_Clock_delete(GAE_Clock_t* clock) {
	free(clock->platformData);
	free(clock);
	clock = 0;
}

GAE_Clock_t* GAE_Clock_reset(GAE_Clock_t* clock) {
	GAE_Clock_Linux_t* linuxClock = (GAE_Clock_Linux_t*)clock->platformData;
	struct timespec time;

	linuxClock->startTime = getCurrentTime(&time);
	linuxClock->currentTime = linuxClock->startTime;

	return clock;
}

GAE_Clock_t* GAE_Clock_update(GAE_Clock_t* clock) {
	GAE_Clock_Linux_t* linuxClock = (GAE_Clock_Linux_t*)clock->platformData;
	struct timespec time;

	clock_gettime(CLOCK_MONOTONIC, &time);
	linuxClock->currentTime = getCurrentTime(&time);
	linuxClock->currentDelta = linuxClock->currentTime - linuxClock->startTime;

	clock->deltaTime = (float)linuxClock->currentDelta;
	clock->currentTime = (float)linuxClock->currentTime;

	return clock;
}

GAE_Clock_t* GAE_Clock_pause(GAE_Clock_t* clock) {
	GAE_Clock_Linux_t* linuxClock = (GAE_Clock_Linux_t*)clock->platformData;
	struct timespec time;

	clock_gettime(CLOCK_MONOTONIC, &time);
	linuxClock->pausedTime = getCurrentTime(&time);
	
	clock->isPaused = GAE_TRUE;

	return clock;
}

GAE_Clock_t* GAE_Clock_resume(GAE_Clock_t* clock) {
	GAE_Clock_Linux_t* linuxClock = (GAE_Clock_Linux_t*)clock->platformData;
	struct timespec time;

	clock_gettime(CLOCK_MONOTONIC, &time);
	linuxClock->currentTime = getCurrentTime(&time);
	linuxClock->startTime += (linuxClock->currentTime - linuxClock->pausedTime);
	
	clock->isPaused = GAE_FALSE;

	return clock;
}

double getCurrentTime(const struct timespec* time) {
  return ((double)(time->tv_sec) + (double)(time->tv_nsec * 0.000000001));
}
