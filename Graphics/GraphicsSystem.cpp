#include "GraphicsSystem.h"

#if defined(LINUX)
	#include "Platform/Linux/LinuxRenderPlatform.h"
#elif defined(PANDORA)
	#include "Platform/Pandora/PandoraRenderPlatform.h"
#elif defined(ANDROID)
	#include "Platform/Android/AndroidRenderPlatform.h"
#elif defined(IOS)
	#include "Platform/iOS/iOSRenderPlatform.h"
#elif defined(DARWIN)
	#include "Platform/Darwin/DarwinRenderPlatform.h"
#elif defined(WIN32)
	#include "Platform/Win32/Win32RenderPlatform.h"
#endif

using namespace GLESGAE;

GraphicsSystem::GraphicsSystem(const RenderPipeline renderPipeline)
: mRenderPipeline(renderPipeline)
, mRenderPlatform(0)
{
}

GraphicsSystem::~GraphicsSystem()
{
	shutdown();
}

bool GraphicsSystem::initialise()
{
	if (0 == mRenderPlatform) {
		#if defined(LINUX)
			mRenderPlatform = new LinuxRenderPlatform;
		#elif defined(PANDORA)
			mRenderPlatform = new PandoraRenderPlatform;
		#elif defined(ANDROID)
			mRenderPlatform = new AndroidRenderPlatform;
		#elif defined(IOS)
			mRenderPlatform = new iOSRenderPlatform;
		#elif defined(DARWIN)
			mRenderPlatform = new DarwinRenderPlatform;
		#elif defined(WIN32)
			mRenderPlatform = new Win32RenderPlatform;
		#endif
	}
	
	mRenderPlatform->initialise();

	return (0 != mRenderPlatform);
}

void GraphicsSystem::shutdown()
{
	if (0 != mRenderPlatform) {
		#if defined(LINUX)
			delete reinterpret_cast<LinuxRenderPlatform*>(mRenderPlatform);
		#elif defined(PANDORA)
			delete reinterpret_cast<PandoraRenderPlatform*>(mRenderPlatform);
		#elif defined(ANDROID)
			delete reinterpret_cast<AndroidRenderPlatform*>(mRenderPlatform);
		#elif defined(IOS)
			delete reinterpret_cast<iOSRenderPlatform*>(mRenderPlatform);
		#elif defined(DARWIN)
			delete reinterpret_cast<DarwinRenderPlatform*>(mRenderPlatform);
		#elif defined(WIN32)
			delete reinterpret_cast<Win32RenderPlatform*>(mRenderPlatform);
		#endif
			
		mRenderPlatform = 0;
	}
}

