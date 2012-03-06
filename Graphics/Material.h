#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <vector>
#include "../Resources/Resource.h"
#include "Shader.h"
#include "Texture.h"

namespace GLESGAE
{
	class Material
	{
		public:
			Material()
			: mShader()
			, mTextures()
			{
			}

			/// Grab the Shader that's linked to this Material
			const Resource<Shader>& getShader() const { return mShader; }

			/// Set a new Shader on this Material
			void setShader(const Resource<Shader>& shader) { mShader = shader; }
			
			/// Add a Texture
			void addTexture(const Resource<Texture>& texture) { mTextures.push_back(texture); }

			/// Grab a Texture
			Resource<Texture> getTexture(unsigned int index) const
			{ 
				if (true == mTextures.empty()) 
					return Resource<Texture>(0); 
				else 
					return mTextures[index]; 
			}
			
			/// Grab amount of Textures we have
			unsigned int getTextureCount() const { return mTextures.size(); }

		private:
			Resource<Shader> mShader;
			std::vector<Resource<Texture> > mTextures;
	};
}

#endif
