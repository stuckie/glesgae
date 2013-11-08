#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#if defined(SDL2)
	#include "SDL2/SDL2InputSystem.h"
#elif defined(PANDORA)
	#include "Pandora/PandoraInputSystem.h"
#elif defined(GLX)
	#include "Linux/LinuxInputSystem.h"
#elif defined(ANDROID)
	#include "Android/AndroidInputSystem.h"
#endif

#endif
