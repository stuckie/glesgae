#ifndef _SCREEN_RENDER_TARGET_H_
#define _SCREEN_RENDER_TARGET_H_

#include "../RenderTarget.h"

namespace GLESGAE
{
	class ScreenRenderTarget : public RenderTarget
	{
		public:
			ScreenRenderTarget() {}
			~ScreenRenderTarget() {}
			
			/// Bind the Screen Render Target for drawing to.
			void bind();
			
			/// Unbind the Screen Render Target as the current drawing surface.
			void unbind();
	};
}

#endif
