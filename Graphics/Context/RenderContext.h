#ifndef _RENDER_CONTEXT_H_
#define _RENDER_CONTEXT_H_

#include "../../Resources/Resource.h"

namespace GLESGAE
{

	class Camera;
	class Matrix4;
	class Mesh;
	class RenderWindow;
	class RenderContext
	{
		public:
			RenderContext() {}
			virtual ~RenderContext() {}

			/// Initialise this Context
			virtual void initialise() = 0;

			/// Shutdown this Context
			virtual void shutdown() = 0;

			/// Refresh this Context
			virtual void refresh() = 0;

			/// Bind to a Window
			virtual void bindToWindow(RenderWindow* const window) = 0;

			/// Draw a Mesh Object
			virtual void drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform) = 0;
			
			/// Set Camera
			virtual void setCamera(const Resource<Camera>& camera) = 0;
			
			/// Set Texture Matrix
			virtual void setTextureMatrix(const Resource<Matrix4>& matrix) = 0;
			
			/// Enable Alpha Blending
			virtual void enableAlphaBlending() = 0;
			
			/// Disable Alpha Blending
			virtual void disableAlphaBlending() = 0;
	};

}

#endif

