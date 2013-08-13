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

void ShaderGlVboRenderer::drawMesh(Mesh* const mesh, Matrix4* const transform)
{
	if (mState == 0)
		return;
	
	IndexBuffer* const indexBuffer(mesh->getIndexBuffer());
	VertexBuffer* const vertexBuffer(mesh->getVertexBuffer());
	Material* const material(mesh->getMaterial());

	mState->bindShader(material->getShader());
	mState->updateUniforms(material, transform);
	mState->updateTextures(material);
	
	const GLuint a_position(mState->a_position);
	const GLuint a_colour(mState->a_colour);
	const GLuint a_normal(mState->a_normal);
	const GLuint a_texCoord0(mState->a_texCoord0);
	
	if (mLastVertexBuffer != vertexBuffer) {
		mLastVertexBuffer = vertexBuffer;
		if (0 == vertexBuffer->getVboId()) { // TODO: This needs redone to store all VboIds internally
			GLuint* buffer(new GLuint);
			glGenBuffers(1, buffer);
			vertexBuffer->setVboId(buffer);
			glBindBuffer(GL_ARRAY_BUFFER, *buffer);
			switch (vertexBuffer->getType()) {
				case VertexBuffer::FORMAT_STATIC:
					glBufferData(GL_ARRAY_BUFFER, vertexBuffer->getSize(), vertexBuffer->getData(), GL_STATIC_DRAW);
				break;
				case VertexBuffer::FORMAT_STREAM:
					glBufferData(GL_ARRAY_BUFFER, vertexBuffer->getSize(), vertexBuffer->getData(), GL_STREAM_DRAW);
				break;
				case VertexBuffer::FORMAT_DYNAMIC:
					glBufferData(GL_ARRAY_BUFFER, vertexBuffer->getSize(), vertexBuffer->getData(), GL_DYNAMIC_DRAW);
				break;
			};
		}
		else {
			glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer->getVboId());
			if (0 != vertexBuffer->getUpdateData()) {
				//TODO: Assert that this buffer is either stream or dynamic.. should not be updating static buffers!
				VertexBuffer::UpdateData* updateData(vertexBuffer->getUpdateData());
				glBufferSubData(GL_ARRAY_BUFFER, updateData->offset, updateData->size, updateData->data);
				if (false == updateData->retain) {
					delete updateData->data;
					delete updateData;
					vertexBuffer->setUpdateData(0);
				}
			}
		}
		

		const VertexBuffer::Format* meshFormat(vertexBuffer->getFormat());
		for (unsigned int index(0U); index < VertexBuffer::FORMAT_SIZE; ++index) {
			const VertexBuffer::Format* itr(&meshFormat[index]);
			switch (itr->getType()) {
				// Position
				case VertexBuffer::FORMAT_POSITION_2F:
					glVertexAttribPointer(a_position, 2U, GL_FLOAT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_POSITION_3F:
					glVertexAttribPointer(a_position, 3U, GL_FLOAT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_POSITION_4F:
					glVertexAttribPointer(a_position, 4U, GL_FLOAT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_POSITION_2S:
					glVertexAttribPointer(a_position, 2U, GL_SHORT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_POSITION_3S:
					glVertexAttribPointer(a_position, 3U, GL_SHORT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_POSITION_4S:
					glVertexAttribPointer(a_position, 4U, GL_SHORT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_POSITION_2B:
					glVertexAttribPointer(a_position, 2U, GL_BYTE, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_POSITION_3B:
					glVertexAttribPointer(a_position, 3U, GL_BYTE, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_POSITION_4B:
					glVertexAttribPointer(a_position, 4U, GL_BYTE, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				// Normal
				case VertexBuffer::FORMAT_NORMAL_3F:
					glVertexAttribPointer(a_normal, 3U, GL_FLOAT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_NORMAL_3S:
					glVertexAttribPointer(a_normal, 3U, GL_SHORT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_NORMAL_3B:
					glVertexAttribPointer(a_normal, 3U, GL_BYTE, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				// Colour
				case VertexBuffer::FORMAT_COLOUR_4F:
					glVertexAttribPointer(a_colour, 4U, GL_FLOAT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_COLOUR_3F:
					glVertexAttribPointer(a_colour, 3U, GL_FLOAT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_COLOUR_4S:
					glVertexAttribPointer(a_colour, 4U, GL_SHORT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_COLOUR_3S:
					glVertexAttribPointer(a_colour, 3U, GL_SHORT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_COLOUR_4UB:
					glVertexAttribPointer(a_colour, 4U, GL_UNSIGNED_BYTE, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				case VertexBuffer::FORMAT_COLOUR_3UB:
					glVertexAttribPointer(a_colour, 3U, GL_UNSIGNED_BYTE, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				// Texture
				case VertexBuffer::FORMAT_TEXTURE_2F:
					glVertexAttribPointer(a_texCoord0, 2U, GL_FLOAT, GL_FALSE, vertexBuffer->getStride(), reinterpret_cast<char*>(itr->getOffset()));
					break;
				default:
					break;
			};
		}
	}

	if (mLastIndexBuffer != indexBuffer) {
		mLastIndexBuffer = indexBuffer;
		if (0 == indexBuffer->getVboId()) { // TODO: This needs redone to store all VboIds internally
			GLuint* buffer(new GLuint);
			glGenBuffers(1, buffer);
			indexBuffer->setVboId(buffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer);
			switch (indexBuffer->getDrawType()) {
				case IndexBuffer::DRAW_STATIC:
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getSize(), indexBuffer->getData(), GL_STATIC_DRAW);
				break;
				case IndexBuffer::DRAW_DYNAMIC:
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getSize(), indexBuffer->getData(), GL_DYNAMIC_DRAW);
				break;
				case IndexBuffer::DRAW_STREAM:
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getSize(), indexBuffer->getData(), GL_STREAM_DRAW);
				break;
			};
		}
		else {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBuffer->getVboId());
			if (0 != indexBuffer->getUpdateData()) {
				//TODO: Assert that this buffer is either stream or dynamic.. should not be updating static buffers!
				IndexBuffer::UpdateData* updateData(indexBuffer->getUpdateData());
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, updateData->offset, updateData->size, updateData->data);
				if (false == updateData->retain) {
					delete updateData->data;
					delete updateData;
					indexBuffer->setUpdateData(0);
				}
			}
		}
	}
	
	switch (indexBuffer->getType()) {
		case IndexBuffer::INDEX_FLOAT:
			glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_FLOAT, 0);
			break;
		case IndexBuffer::INDEX_UNSIGNED_BYTE:
			glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_BYTE, 0);
			break;
		case IndexBuffer::INDEX_UNSIGNED_SHORT:
			glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_SHORT, 0);
			break;
		default:
			break;
	};
}

#endif // not ES1
