#include "ShaderBasedContext.h"

#ifndef GLES1

#include "../IndexBuffer.h"
#include "../Material.h"
#include "../Mesh.h"
#include "../Texture.h"
#include "../VertexBuffer.h"
#include "../Shader.h"
#include "../ShaderUniformUpdater.h"

using namespace GLESGAE;

ShaderBasedContext::ShaderBasedContext()
: mCurrentShader()
, a_position(GL_INVALID_VALUE)
, a_colour(GL_INVALID_VALUE)
, a_normal(GL_INVALID_VALUE)
, a_texCoord0(GL_INVALID_VALUE)
, a_texCoord1(GL_INVALID_VALUE)
, a_custom0(GL_INVALID_VALUE)
, a_custom1(GL_INVALID_VALUE)
, a_custom2(GL_INVALID_VALUE)
, mCamera()
, mLastVertexBuffer()
, mLastIndexBuffer()
, mLastTexture()
, mLastTextureUnit(GL_INVALID_VALUE)
, mUniformUpdaters()
{
	glEnable(GL_TEXTURE_2D);
}

ShaderBasedContext::~ShaderBasedContext()
{
}

void ShaderBasedContext::enableShaderBasedBlending()
{
	glEnable(GL_BLEND);
}

void ShaderBasedContext::disableShaderBasedBlending()
{
	glDisable(GL_BLEND);
}

void ShaderBasedContext::addUniformUpdater(const std::string& uniformName, const Resource<ShaderUniformUpdater>& updater)
{
	// should probably check and assert if we already have something for this uniform name.
	mUniformUpdaters[uniformName] = updater;
}

void ShaderBasedContext::bindShader(const Resource<Shader>& shader)
{
	if (mCurrentShader != shader) {
		mCurrentShader = shader;
		glUseProgram(shader->getProgramId());
		resetAttributes();
		
		const std::vector<std::pair<std::string, GLint> >& attributes(shader->getAttributeArray());
		for (std::vector<std::pair<std::string, GLint> >::const_iterator itr(attributes.begin()); itr < attributes.end(); ++itr)
			glEnableVertexAttribArray(itr->second);
	}
}

void ShaderBasedContext::resetAttributes()
{
	a_position = GL_INVALID_VALUE;
	a_colour = GL_INVALID_VALUE;
	a_normal = GL_INVALID_VALUE;
	a_texCoord0 = GL_INVALID_VALUE;
	a_texCoord1 = GL_INVALID_VALUE;
	a_custom0 = GL_INVALID_VALUE;
	a_custom1 = GL_INVALID_VALUE;
	a_custom2 = GL_INVALID_VALUE;

	if (mCurrentShader != 0) {
		a_position = mCurrentShader->getAttribute("a_position");
		a_colour = mCurrentShader->getAttribute("a_colour");
		a_normal = mCurrentShader->getAttribute("a_normal");
		a_texCoord0 = mCurrentShader->getAttribute("a_texCoord0");
		a_texCoord1 = mCurrentShader->getAttribute("a_texCoord1");
		a_custom0 = mCurrentShader->getAttribute("a_custom0");
		a_custom1 = mCurrentShader->getAttribute("a_custom1");
		a_custom2 = mCurrentShader->getAttribute("a_custom2");
	}

	if (GL_INVALID_VALUE != a_position)
		glEnableVertexAttribArray(a_position);
	if (GL_INVALID_VALUE != a_colour)
		glEnableVertexAttribArray(a_colour);
	if (GL_INVALID_VALUE != a_normal)
		glEnableVertexAttribArray(a_normal);
	if (GL_INVALID_VALUE != a_texCoord0)
		glEnableVertexAttribArray(a_texCoord0);
	if (GL_INVALID_VALUE != a_texCoord1)
		glEnableVertexAttribArray(a_texCoord1);
	if (GL_INVALID_VALUE != a_custom0)
		glEnableVertexAttribArray(a_custom0);
	if (GL_INVALID_VALUE != a_custom1)
		glEnableVertexAttribArray(a_custom1);
	if (GL_INVALID_VALUE != a_custom2)
		glEnableVertexAttribArray(a_custom2);
}

void ShaderBasedContext::updateUniforms(const Resource<Material>& material, const Resource<Matrix4>& transform)
{
	std::vector<std::pair<std::string, GLint> > uniforms(mCurrentShader->getUniformArray());
	for (std::vector<std::pair<std::string, GLint> >::iterator itr(uniforms.begin()); itr < uniforms.end(); ++itr)
		mUniformUpdaters[itr->first]->update(itr->second, mCamera, material, transform);
}

void ShaderBasedContext::updateTextures(const Resource<Material>& material)
{
	const unsigned int textureCount(material->getTextureCount());

	for (unsigned int currentTexture(0U); currentTexture < textureCount; ++currentTexture) {
		GLenum currentTextureUnit(GL_TEXTURE0 + currentTexture);
		if (currentTextureUnit != mLastTextureUnit) {
			glActiveTexture(currentTextureUnit);
			mLastTextureUnit = currentTextureUnit;
		}
		
		const Resource<Texture>& texture(material->getTexture(currentTexture));
		if (mLastTexture != texture) {
			mLastTexture = texture;
			glBindTexture(GL_TEXTURE_2D, texture->getId());
		}
	}
}

void ShaderBasedContext::drawMeshShaderBased(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform)
{
	if (mCamera == 0)
		return;
		
	const Resource<IndexBuffer>& indexBuffer(mesh->getIndexBuffer());
	const Resource<VertexBuffer>& vertexBuffer(mesh->getVertexBuffer());
	const Resource<Material>& material(mesh->getMaterial());

	bindShader(material->getShader());
	updateUniforms(material, transform);
	updateTextures(material);
	
	if (mLastVertexBuffer != vertexBuffer) {
		mLastVertexBuffer = vertexBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getVboId());

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
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getVboId());
	}
	
	switch (indexBuffer->getFormat()) {
		case IndexBuffer::FORMAT_FLOAT:
			glDrawElements(GL_TRIANGLES, indexBuffer->getSize(), GL_FLOAT, 0);
			break;
		case IndexBuffer::FORMAT_UNSIGNED_BYTE:
			glDrawElements(GL_TRIANGLES, indexBuffer->getSize(), GL_UNSIGNED_BYTE, 0);
			break;
		case IndexBuffer::FORMAT_UNSIGNED_SHORT:
			glDrawElements(GL_TRIANGLES, indexBuffer->getSize(), GL_UNSIGNED_SHORT, 0);
			break;
		default:
			break;
	};
}

#endif

