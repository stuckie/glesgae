#ifndef _ANDROID_RENDER_WINDOW_H_
#define _ANDROID_RENDER_WINDOW_H_

#include "../RenderWindow.h"

namespace GLESGAE
{
	class AndroidRenderWindow : public RenderWindow
	{
		public:
			AndroidRenderWindow(const char* windowName, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen);
			~AndroidRenderWindow();

			/// Open the Window
			void open();
			
			/// Refresh the Window
			void refresh();

			/// Close this window
			void close();

			/// Returns the Display for platform specific bits
			void* getDisplay() const { return mDisplay; }

			/// Returns the Window for platform specific bits
			void* getWindow() const { return mWindow; }

		private:
			// No Copying
			AndroidRenderWindow(const AndroidRenderWindow&);
			AndroidRenderWindow& operator=(const AndroidRenderWindow&);
			
			void* mDisplay;
			void* mWindow;
	};

}

#endif

