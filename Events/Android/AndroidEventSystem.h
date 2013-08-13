#ifndef _ANDROID_EVENT_SYSTEM_H_
#define _ANDROID_EVENT_SYSTEM_H_

#include <android_native_app_glue.h>

namespace GLESGAE
{
	class RenderWindow;
	class AndroidRenderWindow;
	class EventSystem : public CommonEventSystem
	{
		public:
			EventSystem();
			~EventSystem();

			/// Update the Event System
			void update();

			/// Bind to the Window
			void bindToWindow(RenderWindow* const window);
			
			/// Android callback for handling input
			static int32_t handleAndroidInput(struct android_app* app, AInputEvent* event);
			
			/// Android callback for handling commands ( state changes, for instance )
			static void handleAndroidCommand(struct android_app* app, int32_t command);

		private:
			// No Copying
			EventSystem(const EventSystem&);
			EventSystem& operator=(const EventSystem&);
			
			bool mActive;
			AndroidRenderWindow* mWindow;
	};
}

#endif
