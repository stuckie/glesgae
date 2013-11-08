#include "../../GraphicsSystem.h"

#include <stdlib.h>

GAE_GraphicsSystem_t* GAE_GraphicsSystem_create() {
	GAE_GraphicsSystem_t* system = (GAE_GraphicsSystem_t*)malloc(sizeof(GAE_GraphicsSystem_t));
	system->window = 0;
	system->context = 0;
	system->renderer = 0;

	return system;
}

void GAE_GraphicsSystem_delete(GAE_GraphicsSystem_t* system) {
	free(system);
	system = 0;
}
