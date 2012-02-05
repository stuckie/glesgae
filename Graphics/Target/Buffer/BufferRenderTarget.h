#ifndef _BUFFER_RENDER_TARGET_H_
#define _BUFFER_RENDER_TARGET_H_

#include "../RenderTarget.h"

namespace GLESGAE
{
	class BufferRenderTarget : public RenderTarget
	{
		public:
			BufferRenderTarget(const RenderTarget::Options options);
			~BufferRenderTarget();
			
			/// Bind the Screen Render Target for drawing to.
			void bind();
			
			/// Unbind the Screen Render Target as the current drawing surface.
			void unbind();
	};
}

#endif
