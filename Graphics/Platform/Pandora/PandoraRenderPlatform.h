#ifndef _PANDORA_RENDER_PLATFORM_H_
#define _PANDORA_RENDER_PLATFORM_H_

#include "../RenderPlatform.h"
#include "../../Context/Pandora/PandoraRenderContext.h"
#include "../../Window/RenderWindow.h"
#include "../../../Resources/Resource.h"

namespace GLESGAE
{
	class PandoraRenderPlatform : public RenderPlatform
	{
		public:
			PandoraRenderPlatform();
			~PandoraRenderPlatform();
			
			/// Initialise this PandoraRenderPlatform.
			void initialise();
			
			/// Shutdown this PandoraRenderPlatform.
			void shutdown();
			
			/// Refresh this PandoraRenderPlatform.
			void refresh();
			
			/// Create a Window.
			Resource<RenderWindow> createWindow(const char* name, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen);
			
			/// Create a Render Context
			Resource<RenderContext> createContext();
	};
}

#endif
