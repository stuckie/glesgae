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
			
			/// Initialise the Render Platform
			bool initialise();
			
			/// Grab The Render Platform.
			template <typename T_RenderPlatform> T_RenderPlatform& getRenderPlatform();
			
			/// Grab standard Render Platform.
			RenderPlatform& getRenderPlatform() { return *mRenderPlatform; }
			
			/// Shutdown the Graphics System.
			void shutdown();
			
		private:
			// No copying
			GraphicsSystem(const GraphicsSystem&);
			GraphicsSystem& operator=(const GraphicsSystem&);
			
			RenderPipeline mRenderPipeline;
			RenderPlatform* mRenderPlatform;
	};
	
	template <typename T_RenderPlatform> T_RenderPlatform& GraphicsSystem::getRenderPlatform()
	{
		return (*reinterpret_cast<T_RenderPlatform*>(mRenderPlatform));
	}
}

#endif
