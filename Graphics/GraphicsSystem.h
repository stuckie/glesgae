#ifndef _GRAPHICS_SYSTEM_H_
#define _GRAPHICS_SYSTEM_H_

#include <string>
#include "../Resources/Resource.h"
#include "Context/RenderContext.h"
#include "Platform/RenderPlatform.h"
#include "Window/RenderWindow.h"

namespace GLESGAE
{
	class GraphicsSystem
	{
		public:
			enum RenderPipeline
			{
				PLATFORM_DEFAULT
			,	SHADER_BASED_RENDERING
			,	FIXED_FUNCTION_RENDERING
			};
			
			GraphicsSystem(const RenderPipeline renderPipeline = PLATFORM_DEFAULT);
			~GraphicsSystem();
			
			/// Initialise with the following Window Dimensions.
			bool initialise(const std::string& windowName, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen);
			
			/// Grab The Render Platform.
			template <typename T_RenderPlatform> T_RenderPlatform& getRenderPlatform();
			
			/// Grab standard Render Platform.
			RenderPlatform& getRenderPlatform() { return *mRenderPlatform; }
			
			/// Get Current Context.
			Resource<RenderContext> getCurrentContext() { return mCurrentRenderContext; }
			
			/// Get Current Window.
			Resource<RenderWindow> getCurrentWindow() { return mCurrentRenderWindow; }
			
			/// Shutdown the Graphics System.
			void shutdown();
			
		private:
			// No copying
			GraphicsSystem(const GraphicsSystem&);
			GraphicsSystem& operator=(const GraphicsSystem&);
			
			RenderPipeline mRenderPipeline;
			RenderPlatform* mRenderPlatform;
			Resource<RenderContext> mCurrentRenderContext;
			Resource<RenderWindow> mCurrentRenderWindow;
	};
	
	template <typename T_RenderPlatform> T_RenderPlatform& GraphicsSystem::getRenderPlatform()
	{
		return (*reinterpret_cast<T_RenderPlatform*>(mRenderPlatform));
	}
}

#endif
