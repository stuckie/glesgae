#ifndef _PLATFORM_H_
#define _PLATFORM_H_

struct GAE_GraphicsSystem_s;
struct GAE_EventSystem_s;
struct GAE_InputSystem_s;
struct GAE_Lifecycle_s;
struct GAE_StateStack_s;
struct GAE_Clock_s;
struct GAE_Logger_s;

/* These need to be filled in via the user */
typedef struct GAE_Platform_s {
	struct GAE_GraphicsSystem_s* graphicsSystem;
	struct GAE_EventSystem_s* eventSystem;
	struct GAE_InputSystem_s* inputSystem;
	struct GAE_Lifecycle_s* lifecycle;
	struct GAE_StateStack_s* stateStack;
	struct GAE_Clock_s* mainClock;
	struct GAE_Logger_s* logger;
	void* userData;
	void* platform;
} GAE_Platform_t;


#if defined(SDL2)
	#include "SDL2/SDL2Platform.h"
#elif defined(PANDORA)
	#include "Pandora/PandoraPlatform.h"
#elif defined(LINUX)
	#include "Linux/LinuxPlatform.h"
#elif defined(WIN32)
	#include "Win32/Win32Platform.h"
#elif defined(DARWIN)
	#include "Darwin/DarwinPlatform.h"
#elif defined(IOS)
	#include "iOS/iOSPlatform.h"
#elif defined(ANDROID)
	#include "Android/AndroidPlatform.h"
#endif

#endif
