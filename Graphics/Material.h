#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <vector>
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
			
			Material(const Material& material)
			: mShader(material.mShader)
			, mTextures(material.mTextures)
			{
			}
			
			Material& operator=(const Material& material)
			{
				if (this != &material) {
					mShader = material.mShader;
					mTextures = material.mTextures;
				}
				
				return *this;
			}

			/// Grab the Shader that's linked to this Material
			Shader* getShader() const { return mShader; }

			/// Set a new Shader on this Material
			void setShader(Shader* const shader) { mShader = shader; }
			
			/// Add a Texture
			void addTexture(Texture* const texture) { mTextures.push_back(texture); }

			/// Grab a Texture
			Texture* getTexture(unsigned int index) const
			{ 
				if (true == mTextures.empty()) 
					return 0; 
				else
					return mTextures[index]; 
			}
			
			/// Grab amount of Textures we have
			unsigned int getTextureCount() const { return mTextures.size(); }

		private:
			Shader* mShader;
			std::vector<Texture*> mTextures;
	};
}

#endif

