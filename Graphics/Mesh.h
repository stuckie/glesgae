#ifndef _MESH_H_
#define _MESH_H_

namespace GLESGAE
{
	class VertexBuffer;
	class IndexBuffer;
	class Material;
	class Mesh
	{
		public:
			Mesh(VertexBuffer* const vertexBuffer
			,	IndexBuffer* const indexBuffer
			,	Material* const material)
			: mVertexBuffer(vertexBuffer)
			, mIndexBuffer(indexBuffer)
			, mMaterial(material)
			{
			}
			
			Mesh(const Mesh& mesh)
			: mVertexBuffer(mesh.mVertexBuffer)
			, mIndexBuffer(mesh.mIndexBuffer)
			, mMaterial(mesh.mMaterial)
			{
			}
			
			Mesh& operator=(const Mesh& mesh)
			{
				if (this != &mesh) {
					mVertexBuffer = mesh.mVertexBuffer;
					mIndexBuffer = mesh.mIndexBuffer;
					mMaterial = mesh.mMaterial;
				}
				
				return *this;
			}
			
			/// Grab the current Vertex Buffer - read-only
			VertexBuffer* getVertexBuffer() const { return mVertexBuffer; }
			
			/// Grab the current Index Buffer - read-only
			IndexBuffer* getIndexBuffer() const { return mIndexBuffer; }
			
			/// Grab the current Material - read-only
			Material* getMaterial() const { return mMaterial; }
			
			/// Grab an Editable Vertex Buffer
			VertexBuffer* editVertexBuffer() { return mVertexBuffer; }
			
			/// Grab an Editable Index Buffer
			IndexBuffer* editIndexBuffer() { return mIndexBuffer; }
			
			/// Grab an Editable Material
			Material* editMaterial() { return mMaterial; }
			
		private:
			VertexBuffer* mVertexBuffer;
			IndexBuffer* mIndexBuffer;
			Material* mMaterial;
	};
}

#endif
