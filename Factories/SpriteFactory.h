#ifndef _SPRITE_FACTORY_H_
#define _SPRITE_FACTORY_H_

#include "../Resources/Resource.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Shader.h"
#include "../Maths/Vector2.h"

namespace GLESGAE
{
	//! Give the Sprite Factory a texture, along with the necessary Resource Bank ids, and it'll create Sprite Meshes for you.
	//! You can grab Meshes from it via specifying the UVST you want from your Texture.
	//! All Meshes will be unit size, so resize as you see fit.
	class Mesh;
	class SpriteFactory
	{
		public:
			struct Settings
			{
				Resources::Locator mesh;
				Resources::Locator vertex;
				Resources::Locator index;
				Resources::Locator material;
				Resources::Locator shader;
			
				Settings() : mesh(), vertex(), index(), material(), shader() {}
			};
		
			SpriteFactory(const Resource<Texture>& texture, const Settings& settings)
			: mTexture(texture)
			, mSettings(settings)
			{
				// Really should check that settings struct to ensure all the important bits are in there...
			}
			
			//! Create a Sprite Mesh from the given UVST and placed in this factory's registered Bank with the given Group Id.
			//! You specify your UVST in terms of pixels, and the Factory will automatically convert them into the correct co-ordinates.
			//! This returns a Resource Locator with where the Sprite Mesh has been created.
			Resources::Locator create(const Vector2& scale, const unsigned int u, const unsigned int v, const unsigned int s, const unsigned int t);
			
			protected:
				/// Helper function to make a Sprite Mesh.
				Mesh* makeSprite(const Vector2& scale, const Resource<Shader>& shader, const float u, const float v, const float s, const float t);
				
				/// Helper function to generate a shader if need be.
				Shader* makeSpriteShader();
			
			private:
				Resource<Texture> mTexture;
				Settings mSettings;
	};
}

#endif

