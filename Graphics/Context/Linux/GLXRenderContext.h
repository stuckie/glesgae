#ifndef _GLX_RENDER_CONTEXT_H_
#define _GLX_RENDER_CONTEXT_H_

#include "GLee.h"

#include "../RenderContext.h"

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
			void setRenderer(Renderer* const renderer);
			
			/// Draw a Mesh Object with the specified Transform.
			void drawMesh(Mesh* const mesh, Matrix4* const transform);
			
			/// Create a new Render Target.
			RenderTarget* createRenderTarget(const RenderTarget::Type type, const RenderTarget::Options options);
			
			/// Get the Render State.
			RenderState* getRenderState();
			
			/// Set the Render State.
			void setRenderState(RenderState* const state);
			
			/// Bind us to a Window.
			void bindToWindow(RenderWindow* const window);
			
			/// Get bound window.
			RenderWindow* getWindow() const;
			
		private:
			// No Copying
			GLXRenderContext(const GLXRenderContext&);
			GLXRenderContext& operator=(const GLXRenderContext&);
			
			X11RenderWindow* mWindow;
			RenderState* mRenderState;
			Renderer* mRenderer;
			GLXContext mContext;
	};
}

#endif
