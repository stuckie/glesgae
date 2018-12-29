#ifndef _SDL2_PLATFORM_H_
#define _SDL2_PLATFORM_H_

#include "../../GAE_Types.h"
#include "SDL2/SDL.h"

#define PLATFORM_MAIN					\
GAE_Platform_t* GAE_PLATFORM;				\
int main(int argc, char* argv[]) {			\
	GAE_BOOL isApplicationRunning = GAE_TRUE;	\

#define PLATFORM_INIT					\
	GAE_PLATFORM = GAE_Platform_create();		\
	GAE_UNUSED(argc);				\
	GAE_UNUSED(argv);				\
	SDL_Init(SDL_INIT_EVERYTHING);

#define PLATFORM_LOOP								\
	(*GAE_PLATFORM->lifecycle->onCreate)();					\
	(*GAE_PLATFORM->lifecycle->onWindowCreate)();				\
	(*GAE_PLATFORM->lifecycle->onStart)();					\
	(*GAE_PLATFORM->lifecycle->onResume)();					\
										\
	while (GAE_TRUE == isApplicationRunning)				\
		isApplicationRunning = (*GAE_PLATFORM->lifecycle->onLoop)();	\
										\
	(*GAE_PLATFORM->lifecycle->onPause)();					\
	(*GAE_PLATFORM->lifecycle->onStop)();					\
	(*GAE_PLATFORM->lifecycle->onDestroy)();				\

#define PLATFORM_END				\
	GAE_Platform_delete(GAE_PLATFORM);	\
	GAE_PLATFORM = 0;			\
	SDL_Quit();				\
	return 0;				\
}

extern GAE_Platform_t* GAE_PLATFORM;

GAE_Platform_t* GAE_Platform_create(void);
void GAE_Platform_delete(GAE_Platform_t* platform);

#endif

