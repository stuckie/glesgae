#ifndef _RENDER_TARGET_H_
#define _RENDER_TARGET_H_

namespace GLESGAE
{
	class RenderTarget
	{
		public:
			enum Type {
				TARGET_SCREEN
			,	TARGET_BUFFER
			,	TARGET_TEXTURE
			};
			
			enum Options {
				OPTIONS_WITH_COLOUR
			,	OPTIONS_WITH_DEPTH
			,	OPTIONS_WITH_STENCIL
			,	OPTIONS_WITH_COLOUR_AND_DEPTH
			,	OPTIONS_WITH_COLOUR_AND_STENCIL
			,	OPTIONS_WITH_DEPTH_AND_STENCIL
			,	OPTIONS_WITH_COLOUR_DEPTH_AND_STENCIL
			};
			
			virtual ~RenderTarget() {}
			
			/// Bind and Start Drawing to this Render Target.
			virtual void bind() = 0;
			
			/// Unbind End Drawing to this Render Target.
			virtual void unbind() = 0;
	};
}

#endif