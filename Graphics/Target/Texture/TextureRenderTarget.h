#ifndef _TEXTURE_RENDER_TARGET_H_
#define _TEXTURE_RENDER_TARGET_H_

#include "../RenderTarget.h"
#include "../../Texture.h"
#include "../../../Resources/Resource.h"

namespace GLESGAE
{
	class TextureRenderTarget : public RenderTarget
	{
		public:
			TextureRenderTarget(const RenderTarget::Options options);
			~TextureRenderTarget();
			
			/// Set the Texture this Target is bound to.
			void setTexture(const Resource<Texture>& texture);
			
			/// Bind the Render Target for drawing to.
			void bind();
			
			/// Unbind the Render Target as the current drawing surface.
			void unbind();
		private:
			Resource<Texture> mTexture;
			unsigned int mFB;
			unsigned int mRB;
	};
}

#endif
