#ifndef _X11_EVENT_SYSTEM_H_
#define _X11_EVENT_SYSTEM_H_

#include "../../Resources/Resource.h"

namespace GLESGAE
{
	class X11RenderWindow;
	class EventSystem : public CommonEventSystem
	{
		public:
			EventSystem();
			~EventSystem();

			/// Update the Event System
			void update();

			/// Bind to the Window
			void bindToWindow(const Resource<RenderWindow>& window);

		private:
			// No Copying
			EventSystem(const EventSystem&);
			EventSystem& operator=(const EventSystem&);
			
			bool mActive;
			Resource<X11RenderWindow> mWindow;
	};
}

#endif
