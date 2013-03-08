#ifndef _RENDER_CONTEXT_H_
#define _RENDER_CONTEXT_H_

#include "../Target/RenderTarget.h"

namespace GLESGAE
{
	class Matrix4;
	class Mesh;
	class Renderer;
	class RenderState;
	class RenderWindow;
	class RenderContext
	{
		public:
			virtual ~RenderContext() {}
			
			/// Initialise the Context
			virtual void initialise() = 0;
			
			/// Refresh the Context
			virtual void refresh() = 0;
			
			/// Shutdown the Context
			virtual void shutdown() = 0;
			
			/// Set the Renderer
			virtual void setRenderer(Renderer* const renderer) = 0;
			
			/// Draw a Mesh Object with the specified Transform.
			virtual void drawMesh(Mesh* const mesh, Matrix4* const transform) = 0;
			
			/// Retrieve the State Object.
			virtual RenderState* getRenderState() = 0;
			
			/// Create a new Render Target.
			virtual RenderTarget* createRenderTarget(const RenderTarget::Type type, const RenderTarget::Options options) = 0;
			
			/// Bind to this Window.
			virtual void bindToWindow(RenderWindow* const window) = 0;
	};

}

#endif

