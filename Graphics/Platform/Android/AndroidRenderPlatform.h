#ifndef _Android_RENDER_PLATFORM_H_
#define _Android_RENDER_PLATFORM_H_

#include "../RenderPlatform.h"
#include "../../Context/Android/AndroidRenderContext.h"
#include "../../Window/RenderWindow.h"
#include "../../../Resources/Resource.h"

namespace GLESGAE
{
	class AndroidRenderPlatform : public RenderPlatform
	{
		public:
			AndroidRenderPlatform();
			~AndroidRenderPlatform();
			
			/// Initialise this AndroidRenderPlatform.
			void initialise();
			
			/// Shutdown this AndroidRenderPlatform.
			void shutdown();
			
			/// Refresh this AndroidRenderPlatform.
			void refresh();
			
			/// Create a Window.
			Resource<RenderWindow> createWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen);
			
			/// Create a Render Context
			Resource<RenderContext> createContext();
	};
}

#endif
