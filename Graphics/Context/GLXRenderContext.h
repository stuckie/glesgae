#ifndef _GLX_RENDER_CONTEXT_H_
#define _GLX_RENDER_CONTEXT_H_

#if defined(GLX)
	#include "../GLee.h"
#elif defined(PANDORA)
	#include <GLES2/gl2.h>
#endif

#include "RenderContext.h"
#include "FixedFunctionContext.h"
#include "ShaderBasedContext.h"
#include "../../Resources/Resource.h"

namespace GLESGAE
{

	class Camera;
	class Mesh;
	class Matrix4;
	class RenderWindow;
	class X11RenderWindow;
	class GLXRenderContext : public RenderContext, public FixedFunctionContext, public ShaderBasedContext
	{
		public:
			GLXRenderContext();
			~GLXRenderContext();

			/// Initialise this Context
			void initialise();

			/// Shutdown this Context
			void shutdown();

			/// Refresh this Context
			void refresh();

			/// Bind us to a Window
			void bindToWindow(RenderWindow* const window);

			/// Set whether this should use the Shader Pipeline or not - specific to this class
			void useShaderBasedContext(const bool useShaders) { mShaderBased = useShaders; }

			/// Draw A Mesh Object - acts as a switch to call the correct function depending on if we're shader-based or not.
			void drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform) { mShaderBased ? drawMeshShaderBased(mesh, transform) : drawMeshFixedFunction(mesh, transform); }
			
			/// Set the Camera to the correct rendering context
			void setCamera(const Resource<Camera>& camera) { mShaderBased ? setShaderBasedCamera(camera) : setFixedFunctionCamera(camera); }
			
			/// Set the Texture Matrix
			void setTextureMatrix(const Resource<Matrix4>& matrix) { mShaderBased ? void(matrix) : setFixedFunctionTextureMatrix(matrix); }
			
			/// Enable Alpha Blending
			void enableAlphaBlending() { mShaderBased ? enableShaderBasedBlending() : enableFixedFunctionBlending(); }
			
			/// Disable Alpha Blending
			void disableAlphaBlending() { mShaderBased ? disableShaderBasedBlending() : disableFixedFunctionBlending(); }

		private:
			// No Copying
			GLXRenderContext(const GLXRenderContext&);
			GLXRenderContext& operator=(const GLXRenderContext&);
			
			X11RenderWindow* mWindow;
			GLXContext mContext;
			bool mShaderBased;
	};

}

#endif

