#include "ShaderGLVboRenderer.h"

#include "../../IndexBuffer.h"
#include "../../Material.h"
#include "../../Mesh.h"
#include "../../Texture.h"
#include "../../VertexBuffer.h"
#include "../../Shader.h"
#include "../../ShaderUniformUpdater.h"
#include "../../State/GLES2/GLES2State.h"

#if !defined(GLES1)

using namespace GLESGAE;

ShaderGlVboRenderer::ShaderGlVboRenderer()
: mLastVertexBuffer()
, mLastIndexBuffer()
, mLastTexture()
, mState()
{
}

ShaderGlVboRenderer::~ShaderGlVboRenderer()
{
}

void ShaderGlVboRenderer::drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform)
{
	if (mState == 0)
		return;
		
	const Resource<IndexBuffer>& indexBuffer(mesh->getIndexBuffer());
	const Resource<VertexBuffer>& vertexBuffer(mesh->getVertexBuffer());
	const Resource<Material>& material(mesh->getMaterial());

	mState->bindShader(material->getShader());
	mState->updateUniforms(material, transform);
	mState->updateTextures(material);
	
	const GLuint a_position(mState->a_position);
	const GLuint a_colour(mState->a_colour);
	const GLuint a_normal(mState->a_normal);
	const GLuint a_texCoord0(mState->a_texCoord0);
	
	if (mLastVertexBuffer != vertexBuffer) {
		mLastVertexBuffer = vertexBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer->getVboId());

		const VertexBuffer::Format* meshFormat(vertexBuffer->getFormat());
		for (unsigned int index(0U); index < VertexBuffer::FORMAT_SIZE; ++index) {
			const VertexBuffer::Format* itr(&meshFormat[index]);
	 		switch (itr->getType()) {
	 			// Position
	 			case VertexBuffer::FORMAT_POSITION_2F:
					glVertexAttribPointer(a_position, 2U, GL_FLOAT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_POSITION_3F:
					glVertexAttribPointer(a_position, 3U, GL_FLOAT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_POSITION_4F:
					glVertexAttribPointer(a_position, 4U, GL_FLOAT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_POSITION_2S:
					glVertexAttribPointer(a_position, 2U, GL_SHORT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_POSITION_3S:
					glVertexAttribPointer(a_position, 3U, GL_SHORT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_POSITION_4S:
					glVertexAttribPointer(a_position, 4U, GL_SHORT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_POSITION_2B:
					glVertexAttribPointer(a_position, 2U, GL_BYTE, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_POSITION_3B:
					glVertexAttribPointer(a_position, 3U, GL_BYTE, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_POSITION_4B:
					glVertexAttribPointer(a_position, 4U, GL_BYTE, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			// Normal
	 			case VertexBuffer::FORMAT_NORMAL_3F:
					glVertexAttribPointer(a_normal, 3U, GL_FLOAT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_NORMAL_3S:
					glVertexAttribPointer(a_normal, 3U, GL_SHORT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_NORMAL_3B:
					glVertexAttribPointer(a_normal, 3U, GL_BYTE, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			// Colour
	 			case VertexBuffer::FORMAT_COLOUR_4F:
					glVertexAttribPointer(a_colour, 4U, GL_FLOAT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_COLOUR_3F:
					glVertexAttribPointer(a_colour, 3U, GL_FLOAT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_COLOUR_4S:
					glVertexAttribPointer(a_colour, 4U, GL_SHORT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_COLOUR_3S:
					glVertexAttribPointer(a_colour, 3U, GL_SHORT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_COLOUR_4UB:
					glVertexAttribPointer(a_colour, 4U, GL_UNSIGNED_BYTE, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			case VertexBuffer::FORMAT_COLOUR_3UB:
					glVertexAttribPointer(a_colour, 3U, GL_UNSIGNED_BYTE, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			// Texture
	 			case VertexBuffer::FORMAT_TEXTURE_2F:
	 				glVertexAttribPointer(a_texCoord0, 2U, GL_FLOAT, GL_FALSE, 0U, reinterpret_cast<char*>(itr->getOffset()));
	 				break;
	 			default:
	 				break;
			};
		}
	}

	if (mLastIndexBuffer != indexBuffer) {
		mLastIndexBuffer = indexBuffer;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBuffer->getVboId());
	}
	
	switch (indexBuffer->getType()) {
		case IndexBuffer::INDEX_FLOAT:
			glDrawElements(GL_TRIANGLES, indexBuffer->getSize(), GL_FLOAT, 0);
			break;
		case IndexBuffer::INDEX_UNSIGNED_BYTE:
			glDrawElements(GL_TRIANGLES, indexBuffer->getSize(), GL_UNSIGNED_BYTE, 0);
			break;
		case IndexBuffer::INDEX_UNSIGNED_SHORT:
			glDrawElements(GL_TRIANGLES, indexBuffer->getSize(), GL_UNSIGNED_SHORT, 0);
			break;
		default:
			break;
	};
}

#endif // not ES1
