#ifndef _GLES2_RENDER_CONTEXT_H_
#define _GLES2_RENDER_CONTEXT_H_

#if defined(PANDORA)
	#include <EGL/egl.h>
#endif

#include "RenderContext.h"
#include "ShaderBasedContext.h"
#include "../../Resources/Resource.h"

namespace GLESGAE
{

	class RenderWindow;
	class X11RenderWindow;
	class GLES2RenderContext : public RenderContext, public ShaderBasedContext
	{
		public:
			GLES2RenderContext();
			~GLES2RenderContext();

			/// Initialise this Context
			void initialise();

			/// Shutdown this Context
			void shutdown();

			/// Refresh this Context
			void refresh();

			/// Bind us to a Window
			void bindToWindow(RenderWindow* const window);

			/// Draw a Mesh Object
			void drawMesh(const Resource<Mesh>& const mesh) { drawMeshShaderBased(mesh); }

			/// Set the Camera
			void setCamera(const Resource<Camera>& const camera) { setShaderBasedCamera(camera); }

			/// Set Texture Matrix
			void setTextureMatrix(const Resource<Matrix4>&) {}

		private:
			// No Copying
			GLES2RenderContext(const GLES2RenderContext&);
			GLES2RenderContext& operator=(const GLES2RenderContext&);
			
			X11RenderWindow* mWindow;
			EGLDisplay  mDisplay;
			EGLContext  mContext;
			EGLSurface  mSurface;
	};

}

#endif
