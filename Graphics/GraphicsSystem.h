#ifndef _GRAPHICS_SYSTEM_H_
#define _GRAPHICS_SYSTEM_H_

#include <string>
#include "../Resources/Resource.h"

namespace GLESGAE
{
	class FixedFunctionContext;
	class Matrix4;
	class Mesh;
	class Camera;
	class RenderContext;
	class RenderWindow;
	class ShaderBasedContext;
	class GraphicsSystem
	{
		public:
			enum RenderType
			{
				SHADER_BASED_RENDERING
			,	FIXED_FUNCTION_RENDERING
			};

			GraphicsSystem(const RenderType renderType);
			~GraphicsSystem();

			/// Initialise with the following Window Dimensions
			bool initialise(const std::string& windowName, const unsigned int width, const unsigned int height, const unsigned int bits, const bool fullscreen);

			/// Shutdown the Graphics System.
			void shutdown();

			/// Begin a new frame
			void beginFrame();
			
			/// Set the current camera
			void setCamera(const Resource<Camera>& camera);
			
			/// Set Texture Matrix
			void setTextureMatrix(const Resource<Matrix4>& matrix);

			/// Draw a Mesh Object
			void drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform);
			
			/// Enable Alpha Blending
			void enableAlphaBlending();
			
			/// Disable Alpha Blending
			void disableAlphaBlending();

			/// End a frame
			void endFrame();

			/// Grab a Window Pointer
			RenderWindow* getWindow() const { return mWindow; }

			/// Grab a Shader Context Pointer
			ShaderBasedContext* getShaderContext() const;

			/// Grab a Fixed Function Context Pointer
			FixedFunctionContext* getFixedContext() const;
			
		private:
			// No copying
			GraphicsSystem(const GraphicsSystem&);
			GraphicsSystem& operator=(const GraphicsSystem&);
			
			RenderType mRenderType;
			RenderContext* mRenderContext;
			RenderWindow* mWindow;
	};
}

#endif
