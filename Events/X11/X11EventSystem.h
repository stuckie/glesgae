#ifndef _X11_EVENT_SYSTEM_H_
#define _X11_EVENT_SYSTEM_H_

namespace GLESGAE
{
	class RenderWindow;
	class X11RenderWindow;
	class EventSystem : public CommonEventSystem
	{
		public:
			EventSystem();
			~EventSystem();

			/// Update the Event System
			void update();

			/// Bind to the Window
			void bindToWindow(RenderWindow* const window);

		private:
			// No Copying
			EventSystem(const EventSystem&);
			EventSystem& operator=(const EventSystem&);
			
			bool mActive;
			X11RenderWindow* mWindow;
	};
}

#endif
