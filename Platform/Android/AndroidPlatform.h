#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <jni.h>
#include <android_native_app_glue.h>
#include "../../Events/EventSystem.h"

#define PLATFORM_MAIN 	\
extern "C" {												\
	void android_main(struct android_app* app)							\
	{												\
		app_dummy();
	
#define PLATFORM_INIT											\
		app->userData = application;								\
		app->onAppCmd = GLESGAE::EventSystem::handleAndroidCommand;				\
		app->onInputEvent = GLESGAE::EventSystem::handleAndroidInput;				\
		platform->setApp(app);									\
													\
		if (0 != app->savedState)								\
			platform->setState(reinterpret_cast<AndroidState*>(app->savedState));
	
#define PLATFORM_LOOP											\
		application->onCreate();								\
		bool applicationRunning(true);								\
		int ident(0);										\
		int events(0);										\
		struct android_poll_source* source(0);							\
		while (true == applicationRunning) {							\
			while ( (ident=ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {	\
			if (0 != source) {								\
					source->process(app, source);					\
				}									\
			}										\
			applicationRunning = application->onLoop();					\
		}
	
#define END_MAIN											\
	}												\
}

class AndroidState;
namespace GLESGAE
{
	class Platform : public BasePlatform
	{
		public:
			Platform();
			virtual ~Platform() {}
			
			/// Get the Android App magic struct.
			android_app* getApp() { return mApp; }
			
			/// Set the Android App magic struct.
			void setApp(android_app* const app) { mApp = app; }
			
			/// Get the Android State for any saved info we may need.
			AndroidState* getState() { return mState; }
			
			/// Set the Android State for any saved info we may need.
			void setState(AndroidState* const state) { mState = state; }
			
		protected:
			struct android_app* 	mApp;
			AndroidState*		mState;
			
		private:
			Platform(const Platform&);
			Platform& operator=(const Platform&);
	};
}

#endif

