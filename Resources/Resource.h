#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "../Utils/HashString.h"

namespace GLESGAE
{
	namespace Resources
	{
		typedef HashString Type;
		typedef unsigned int Id;
		
		// System Resources
		extern Type Camera;
		extern Type Controller;
		extern Type IndexBuffer;
		extern Type Material;
		extern Type Matrix2;
		extern Type Matrix3;
		extern Type Matrix4;
		extern Type Mesh;
		extern Type Shader;
		extern Type ShaderUniformUpdater;
		extern Type Texture;
		extern Type Timer;
		extern Type Vector2;
		extern Type Vector3;
		extern Type Vector4;
		extern Type VertexBuffer;
	}
	
	template <typename T_Type> class Resource
	{
		public:
			Resource(const Resources::Id id) : mId(id) {}
			
			/// Retrieve id
			Resources::Id getId() const { return mId; }
			
		private:
			Resources::Id mId;
	};
}

#endif

