#ifndef _RENDER_PLATFORM_H_
#define _RENDER_PLATFORM_H_

namespace GLESGAE
{
	class RenderContext;
	class RenderWindow;
	class RenderPlatform
	{
		public:
			virtual ~RenderPlatform() {}
			
			/// Initialise this RenderPlatform.
			virtual void initialise() = 0;
			
			/// Shutdown this RenderPlatform.
			virtual void shutdown() = 0;
			
			/// Create a Window.
			virtual RenderWindow* createWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen) = 0;
			
			/// Create a Render Context
			virtual RenderContext* createContext() = 0;
	};
}

#endif

