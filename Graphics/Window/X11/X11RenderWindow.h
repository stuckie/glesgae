#ifndef _X11_RENDER_WINDOW_H_
#define _X11_RENDER_WINDOW_H_

#include "../RenderWindow.h"
#include <X11/Xlib.h>

namespace GLESGAE
{
	class X11RenderWindow : public RenderWindow
	{
		public:
			X11RenderWindow(const char* windowName, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen);
			~X11RenderWindow();

			/// Open the Window
			void open();
			
			/// Refresh the Window
			void refresh();

			/// Close this window
			void close();

			/// Returns the Display for platform specific bits
			Display* getDisplay() const { return mDisplay; }

			/// Returns the Window for platform specific bits
			Window getWindow() const { return mWindow; }

			/// Returns the Delete Message for platform specific bits
			Atom getDeleteMessage() const { return mDeleteMessage; }

		private:
			// No Copying
			X11RenderWindow(const X11RenderWindow&);
			X11RenderWindow& operator=(const X11RenderWindow&);
			
			Display* mDisplay;
			Window mWindow;
			Atom mDeleteMessage;
	};

}

#endif

