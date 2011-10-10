#ifndef _RENDER_CONTEXT_H_
#define _RENDER_CONTEXT_H_

#include "../../Resources/Resource.h"
#include "../Renderer/Renderer.h"
#include "../State/RenderState.h"
#include "../Target/RenderTarget.h"
#include "../Window/RenderWindow.h"

namespace GLESGAE
{
	class Matrix4;
	class Mesh;
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
			virtual void setRenderer(const Resource<Renderer>& renderer) = 0;
			
			/// Draw a Mesh Object with the specified Transform.
			virtual void drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform) = 0;
			
			/// Retrieve the State Object.
			virtual Resource<RenderState> getRenderState() = 0;
			
			/// Create a new Render Target.
			virtual Resource<RenderTarget> createRenderTarget(const RenderTarget::Type type, const RenderTarget::Options options) = 0;
			
			/// Bind to this Window.
			virtual void bindToWindow(const Resource<RenderWindow>& window) = 0;
	};

}

#endif

