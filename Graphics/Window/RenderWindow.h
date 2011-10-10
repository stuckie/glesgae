#ifndef _RENDER_WINDOW_H_
#define _RENDER_WINDOW_H_

namespace GLESGAE
{
	class RenderWindow
	{
		public:
			RenderWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen)
			: mName(name)
			, mWidth(width)
			, mHeight(height)
			, mBPP(bpp)
			, mFullscreen(fullscreen)
			{
			}

			virtual ~RenderWindow() {}
			
			/// Get the Name of this Window.
			const char* getName() const { return mName; }
			
			/// Get the Width of this Window.
			unsigned int getWidth() const { return mWidth; }
			
			/// Get the Height of this Window.
			unsigned int getHeight() const { return mHeight; }
			
			/// Get the BPP of this Window.
			unsigned int getBPP() const { return mBPP; }
			
			/// Is Fullscreen.
			bool isFullscreen() const { return mFullscreen; }
			
			/// Open the Window
			virtual void open() = 0;
			
			/// Close the Window
			virtual void close() = 0;

		protected:
			const char* mName;
			unsigned int mWidth;
			unsigned int mHeight;
			unsigned int mBPP;
			bool mFullscreen;
			
		private:
			// No copying
			RenderWindow(const RenderWindow&);
			RenderWindow& operator=(const RenderWindow&);
	};
}

#endif

