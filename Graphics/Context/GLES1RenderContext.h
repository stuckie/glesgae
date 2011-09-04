#ifndef _GLES1_RENDER_CONTEXT_H_
#define _GLES1_RENDER_CONTEXT_H_

#if defined(PANDORA)
	#include <EGL/egl.h>
#endif

#include "RenderContext.h"
#include "FixedFunctionContext.h"
#include "../../Resources/Resource.h"

namespace GLESGAE
{

	class Camera;
	class Mesh;
	class RenderWindow;
	class X11RenderWindow;
	class GLES1RenderContext : public RenderContext, public FixedFunctionContext
	{
		public:
			GLES1RenderContext();
			~GLES1RenderContext();

			/// Initialise this Context
			void initialise();

			/// Shutdown this Context
			void shutdown();

			/// Refresh this Context
			void refresh();

			/// Bind us to a Window
			void bindToWindow(RenderWindow* const window);

			/// Draw a Mesh object
			void drawMesh(const Resource<Mesh>& mesh) { drawMeshFixedFunction(mesh); }

			/// Set The Camera
			void setCamera(const Resource<Camera>& camera) { setFixedFunctionCamera(camera); }
			
			/// Set Texture Matrix
			void setTextureMatrix(const Resource<Matrix4>& matrix) { setFixedFunctionTextureMatrix(matrix); }

		private:
			// No Copying
			GLES1RenderContext(const GLES1RenderContext&);
			GLES1RenderContext& operator=(const GLES1RenderContext&);
			
			X11RenderWindow* mWindow;
			EGLDisplay  mDisplay;
			EGLContext  mContext;
			EGLSurface  mSurface;
	};

}

#endif
