#ifndef _PANDORA_RENDER_CONTEXT_H_
#define _PANDORA_RENDER_CONTEXT_H_

#include <EGL/egl.h>

#include "../RenderContext.h"

namespace GLESGAE
{
	class X11RenderWindow;
	class RenderTarget;
	class RenderState;
	class Renderer;
	class PandoraRenderContext : public RenderContext
	{
		public:
			PandoraRenderContext();
			~PandoraRenderContext();
			
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
			
			/// Bind us to a Window.
			void bindToWindow(RenderWindow* const window);
			
			/// Get Bound Window
			RenderWindow* getWindow() const;
			
		private:
			// No Copying
			PandoraRenderContext(const PandoraRenderContext&);
			PandoraRenderContext& operator=(const PandoraRenderContext&);
			
			X11RenderWindow* 	mWindow;
			RenderState* 		mRenderState;
			Renderer*			mRenderer;
			EGLDisplay  		mDisplay;
			EGLContext 			mContext;
			EGLSurface  		mSurface;
	};
}

#endif
