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
			
			/// Bind the Render Target for drawing to.
			void bind();
			
			/// Unbind the Render Target as the current drawing surface.
			void unbind();
	};
}

#endif
