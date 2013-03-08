#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../Maths/Vector2.h"

namespace GLESGAE
{
	class Material;
	class Matrix4;
	class Mesh;
	class Sprite
	{
		public:
			Sprite(Material* const material, const Vector2& size, const float u, const float v, const float w, const float h);
			Sprite(const Sprite& sprite);
			Sprite& operator=(const Sprite& sprite);
			~Sprite();
			
			//! Get the Mesh of this Sprite.
			Mesh* getMesh() const;
			
			//! Get the Position of this Sprite.
			const Vector2& getPosition() const;
			
			//! Get the Rotation of this Sprite.
			float getRotation() const;
			
			//! Get the Transform of this Sprite.
			Matrix4* getTransform() const;
			
			//! Set the Position of this Sprite.
			void setPosition(const Vector2& position);
			
			//! Set the Rotation of this Sprite.
			void setRotation(const float rotation);
			
		private:
			Mesh* mMesh;
			Matrix4* mTransform;
			Vector2 mPosition;
			float mRotation;
	};
}

#endif

