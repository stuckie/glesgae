#ifndef _LINUX_RENDER_PLATFORM_H_
#define _LINUX_RENDER_PLATFORM_H_

#include "../RenderPlatform.h"
#include "../../Context/Linux/GLXRenderContext.h"
#include "../../Window/RenderWindow.h"
#include "../../../Resources/Resource.h"

namespace GLESGAE
{
	class LinuxRenderPlatform : public RenderPlatform
	{
		public:
			LinuxRenderPlatform();
			~LinuxRenderPlatform();
			
			/// Initialise this LinuxRenderPlatform.
			void initialise();
			
			/// Shutdown this LinuxRenderPlatform.
			void shutdown();
			
			/// Refresh this LinuxRenderPlatform.
			void refresh();
			
			/// Create a Window.
			Resource<RenderWindow> createWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen);
			
			/// Create a Render Context
			Resource<RenderContext> createContext();
	};
}

#endif
