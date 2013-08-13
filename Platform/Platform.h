#ifndef _BASE_PLATFORM_H_
#define _BASE_PLATFORM_H_

namespace GLESGAE
{
	class BasePlatform
	{
		public:
			virtual ~BasePlatform() {}
	};
}

// Include the platform specifics.

#if defined(PANDORA)
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

