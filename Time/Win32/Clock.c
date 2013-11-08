#include "../Clock.h"

#include <stdlib.h>
#include <Windows.h>

typedef struct GAE_Clock_Win32_s {
	double startTime;
	double currentTime;
	double currentDelta;
	double pausedTime;
	double frequency;
} GAE_Clock_Win32_t;

double getCurrentTime(GAE_Clock_Win32_t* const clock);

GAE_Clock_t* GAE_Clock_create(void) {
	GAE_Clock_t* clock = (GAE_Clock_t*)malloc(sizeof(GAE_Clock_t));
	GAE_Clock_Win32_t* win32Clock = (GAE_Clock_Win32_t*)malloc(sizeof(GAE_Clock_Win32_t));
	LARGE_INTEGER li;

	clock->deltaTime = 0.0F;
	clock->currentTime = 0.0F;
	clock->isPaused = GAE_FALSE;
	clock->platformData = win32Clock;

    if (!QueryPerformanceFrequency(&li))
		return 0;

	win32Clock->frequency = (double)((li.QuadPart)/1000.0);

    QueryPerformanceCounter(&li);
	win32Clock->startTime = (double)li.QuadPart;
	win32Clock->currentTime = win32Clock->startTime;
	win32Clock->currentDelta = 0.0;
	win32Clock->pausedTime = 0.0;

	return clock;
}

void GAE_Clock_delete(GAE_Clock_t* clock) {
	free(clock->platformData);
	free(clock);
	clock = 0;
}

GAE_Clock_t* GAE_Clock_reset(GAE_Clock_t* clock) {
	GAE_Clock_Win32_t* win32Clock = (GAE_Clock_Win32_t*)clock->platformData;

	win32Clock->startTime = getCurrentTime(win32Clock);
	win32Clock->currentTime = win32Clock->startTime;

	return clock;
}

GAE_Clock_t* GAE_Clock_update(GAE_Clock_t* clock) {
	GAE_Clock_Win32_t* win32Clock = (GAE_Clock_Win32_t*)clock->platformData;

	win32Clock->currentTime = getCurrentTime(win32Clock);
	win32Clock->currentDelta = win32Clock->currentTime - win32Clock->startTime;

	clock->deltaTime = (float)win32Clock->currentDelta;
	clock->currentTime = (float)win32Clock->currentTime;

	return clock;
}

GAE_Clock_t* GAE_Clock_pause(GAE_Clock_t* clock) {
	GAE_Clock_Win32_t* win32Clock = (GAE_Clock_Win32_t*)clock->platformData;

	win32Clock->pausedTime = getCurrentTime(win32Clock);
	
	clock->isPaused = GAE_TRUE;

	return clock;
}

GAE_Clock_t* GAE_Clock_resume(GAE_Clock_t* clock) {
	GAE_Clock_Win32_t* win32Clock = (GAE_Clock_Win32_t*)clock->platformData;

	win32Clock->currentTime = getCurrentTime(win32Clock);
	win32Clock->startTime += (win32Clock->currentTime - win32Clock->pausedTime);
	
	clock->isPaused = GAE_FALSE;

	return clock;
}

double getCurrentTime(GAE_Clock_Win32_t* const clock) {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
	return (double)((li.QuadPart - clock->startTime) / clock->frequency);
}
