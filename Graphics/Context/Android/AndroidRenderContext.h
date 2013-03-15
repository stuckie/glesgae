#ifndef _ANDROID_RENDER_CONTEXT_H_
#define _ANDROID_RENDER_CONTEXT_H_

#include <EGL/egl.h>

#include "../RenderContext.h"

namespace GLESGAE
{
	class AndroidRenderWindow;
	class RenderTarget;
	class RenderState;
	class Renderer;
	class AndroidRenderContext : public RenderContext
	{
		public:
			AndroidRenderContext();
			~AndroidRenderContext();
			
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
			
		private:
			// No Copying
			AndroidRenderContext(const AndroidRenderContext&);
			AndroidRenderContext& operator=(const AndroidRenderContext&);
			
			AndroidRenderWindow* 	mWindow;
			RenderState* 			mRenderState;
			Renderer* 				mRenderer;
			EGLDisplay  			mDisplay;
			EGLContext  			mContext;
			EGLSurface  			mSurface;
	};
}

#endif
