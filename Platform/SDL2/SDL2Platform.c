#include "../Platform.h"

#include <stdlib.h>

GAE_Platform_t* GAE_Platform_create(void) {
	GAE_Platform_t* platform = malloc(sizeof(GAE_Platform_t));

	platform->graphicsSystem = 0;
	platform->eventSystem = 0;
	platform->inputSystem = 0;
	platform->lifecycle = 0;
	platform->stateStack = 0;
	platform->mainClock = 0;
	platform->logger = 0;
	platform->userData = 0;

	platform->platform = 0;

	return platform;
}

void GAE_Platform_delete(GAE_Platform_t* platform) {
	free(platform);
	platform = 0;
}

