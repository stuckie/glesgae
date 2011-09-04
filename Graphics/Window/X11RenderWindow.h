#ifndef _X11_RENDER_WINDOW_H_
#define _X11_RENDER_WINDOW_H_

#include "RenderWindow.h"
#include <X11/Xlib.h>

namespace GLESGAE
{

	class X11RenderWindow : public RenderWindow
	{
		public:
			X11RenderWindow();
			~X11RenderWindow();

			/// Open this window with the given name, width and height
			void open(const char* windowName, const unsigned int width, const unsigned int height);

			/// Set this Window's Render Context
			void setContext(RenderContext* const context);

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

