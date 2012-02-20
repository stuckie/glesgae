#ifndef _SCREEN_RENDER_TARGET_H_
#define _SCREEN_RENDER_TARGET_H_

#include "../RenderTarget.h"

namespace GLESGAE
{
	class ScreenRenderTarget : public RenderTarget
	{
		public:
			ScreenRenderTarget() : RenderTarget(RenderTarget::TARGET_SCREEN, RenderTarget::OPTIONS_WITH_COLOUR) {}
			~ScreenRenderTarget() {}
			
			/// Bind the Render Target for drawing to.
			void bind();
			
			/// Unbind the Render Target as the current drawing surface.
			void unbind();
	};
}

#endif
