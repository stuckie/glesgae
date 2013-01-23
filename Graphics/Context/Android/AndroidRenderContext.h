#ifndef _ANDROID_RENDER_CONTEXT_H_
#define _ANDROID_RENDER_CONTEXT_H_

#include <EGL/egl.h>

#include "../RenderContext.h"
#include "../../../Resources/Resource.h"

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
			void setRenderer(const Resource<Renderer>& renderer);
			
			/// Draw a Mesh Object with the specified Transform.
			void drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform);
			
			/// Create a new Render Target.
			Resource<RenderTarget> createRenderTarget(const RenderTarget::Type type, const RenderTarget::Options options);
			
			/// Get the Render State.
			Resource<RenderState> getRenderState();
			
			/// Bind us to a Window.
			void bindToWindow(const Resource<RenderWindow>& window);
			
		private:
			// No Copying
			AndroidRenderContext(const AndroidRenderContext&);
			AndroidRenderContext& operator=(const AndroidRenderContext&);
			
			Resource<AndroidRenderWindow> mWindow;
			Resource<RenderState> mRenderState;
			Resource<Renderer> mRenderer;
			EGLDisplay  mDisplay;
			EGLContext  mContext;
			EGLSurface  mSurface;
	};
}

#endif
