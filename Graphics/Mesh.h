#ifndef _MESH_H_
#define _MESH_H_

#include "../Resources/Resource.h"

namespace GLESGAE
{
	class VertexBuffer;
	class IndexBuffer;
	class Material;
	class Mesh
	{
		public:
			Mesh(const Resource<VertexBuffer>& vertexBuffer
			,	const Resource<IndexBuffer>& indexBuffer
			,	const Resource<Material>& material)
			: mVertexBuffer(vertexBuffer)
			, mIndexBuffer(indexBuffer)
			, mMaterial(material)
			{
			}
			
			/// Grab the current Vertex Buffer - read-only
			const Resource<VertexBuffer>& getVertexBuffer() const { return mVertexBuffer; }
			
			/// Grab the current Index Buffer - read-only
			const Resource<IndexBuffer>& getIndexBuffer() const { return mIndexBuffer; }
			
			/// Grab the current Material - read-only
			const Resource<Material>& getMaterial() const { return mMaterial; }
			
			/// Grab an Editable Vertex Buffer
			Resource<VertexBuffer>& editVertexBuffer() { return mVertexBuffer; }
			
			/// Grab an Editable Index Buffer
			Resource<IndexBuffer>& editIndexBuffer() { return mIndexBuffer; }
			
			/// Grab an Editable Material
			Resource<Material>& editMaterial() { return mMaterial; }
			
		private:
			Resource<VertexBuffer> mVertexBuffer;
			Resource<IndexBuffer> mIndexBuffer;
			Resource<Material> mMaterial;
	};
}

#endif
