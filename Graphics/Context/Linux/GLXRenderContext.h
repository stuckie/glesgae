#ifndef _GLX_RENDER_CONTEXT_H_
#define _GLX_RENDER_CONTEXT_H_

#include "GLee.h"

#include "../RenderContext.h"
#include "../../../Resources/Resource.h"

namespace GLESGAE
{
	class X11RenderWindow;
	class RenderTarget;
	class RenderState;
	class Renderer;
	class GLXRenderContext : public RenderContext
	{
		public:
			GLXRenderContext();
			~GLXRenderContext();
			
			/// Initialise this Context
			void initialise();
			
			/// Refresh this Context
			void refresh();
			
			/// Shutdown this Context
			void shutdown();
			
			/// Set the Renderer
			void setRenderer(const Resource<Renderer>& renderer);
			
			/// Draw a Mesh Object with the specified Transform.
			void drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform);
			
			/// Create a new Render Target.
			Resource<RenderTarget> createRenderTarget(const RenderTarget::Type type, const RenderTarget::Options options);
			
			/// Get the Render State.
			Resource<RenderState> getRenderState();
			
			/// Set the Render State.
			void setRenderState(const Resource<RenderState>& state);
			
			/// Bind us to a Window.
			void bindToWindow(const Resource<RenderWindow>& window);
			
		private:
			// No Copying
			GLXRenderContext(const GLXRenderContext&);
			GLXRenderContext& operator=(const GLXRenderContext&);
			
			Resource<X11RenderWindow> mWindow;
			Resource<RenderState> mRenderState;
			Resource<Renderer> mRenderer;
			GLXContext mContext;
	};
}

#endif
