#ifndef _SPRITE_FACTORY_H_
#define _SPRITE_FACTORY_H_

#include "../Resources/Resource.h"
#include "../Graphics/Material.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Shader.h"
#include "../Maths/Vector2.h"
#include "../Utils/Sprite.h"

namespace GLESGAE
{
	//! Give the Sprite Factory a texture and it'll create Sprite Meshes for you.
	//! You can grab Meshes from it via specifying the UVST you want from your Texture.
	class SpriteFactory
	{
		public:
			SpriteFactory(const Resource<Texture>& texture);
			
			//! Create a Sprite Mesh from the given UVST and placed in this factory's registered Bank with the given Group Id.
			//! You specify your UVST in terms of pixels, and the Factory will automatically convert them into the correct co-ordinates.
			Resource<Sprite> create(const Vector2& size, const unsigned int u, const unsigned int v, const unsigned int s, const unsigned int t);
			
			//! Set a different Sprite Shader if wanted.
			void setShader(const Resource<Shader>& shader);
			
			protected:
				/// Helper function to generate the sprite shader.
				Shader* makeSpriteShader();
			
			private:
				Resource<Material> mMaterial;
	};
}

#endif

