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
			
			RenderTarget(const Type type, const Options options) : mType(type), mOptions(options) {}
			virtual ~RenderTarget() {}
			
			/// Bind and Start Drawing to this Render Target.
			virtual void bind() = 0;
			
			/// Unbind End Drawing to this Render Target.
			virtual void unbind() = 0;
			
			/// Get the type of this RenderTarget
			Type getType() const { return mType; }
			
			/// Get the options of this RenderTarget
			Options getOptions() const { return mOptions; }
			
		private:
			Type mType;
			Options mOptions;
	};
}

#endif
