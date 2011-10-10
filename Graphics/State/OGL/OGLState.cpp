#include "OGLState.h"

#include "../../Camera.h"
#include "../../Shader.h"
#include "../../ShaderUniformUpdater.h"
#include "../../Material.h"
#include "../../Texture.h"
#include "../../../Maths/Matrix4.h"

using namespace GLESGAE;

OGLState::OGLState()
: mCamera()
, mTextureMatrix()
, mTexturing(false)
, mAlphaBlending(false)
, mCurrentShader()
, a_position(GL_INVALID_VALUE)
, a_colour(GL_INVALID_VALUE)
, a_normal(GL_INVALID_VALUE)
, a_texCoord0(GL_INVALID_VALUE)
, a_texCoord1(GL_INVALID_VALUE)
, a_custom0(GL_INVALID_VALUE)
, a_custom1(GL_INVALID_VALUE)
, a_custom2(GL_INVALID_VALUE)
, mLastTexture()
, mLastTextureUnit(GL_INVALID_VALUE)
, mUniformUpdaters()
{
}

OGLState::~OGLState()
{
}

void OGLState::setCamera(const Resource<Camera>& camera)
{
	if (mCamera != camera) {
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(camera->getProjectionMatrix().getData());
		
		glMatrixMode(GL_MODELVIEW);
		Matrix4& viewMatrix(camera->getViewMatrix());
		viewMatrix(0U, 2U) = -viewMatrix(0U, 2U);
		viewMatrix(1U, 2U) = -viewMatrix(1U, 2U);
		viewMatrix(2U, 2U) = -viewMatrix(2U, 2U);
		viewMatrix(3U, 2U) = -viewMatrix(3U, 2U);
		glLoadMatrixf(viewMatrix.getData());
		
		mCamera = camera;
	}
}

void OGLState::setTextureMatrix(const Resource<Matrix4>& matrix)
{
	if (mTextureMatrix != matrix) {
		glMatrixMode(GL_TEXTURE);
		glLoadMatrixf(matrix->getData());
		
		glMatrixMode(GL_MODELVIEW);
		
		mTextureMatrix = matrix;
	}
}

void OGLState::setTexturingEnabled(const bool isEnabled)
{
	switch (isEnabled) {
		case true:
			if (false == mTexturing) {
				glEnable(GL_TEXTURE_2D);
				mTexturing = true;
			}
		break;
		case false:
			if (true == mTexturing) {
				glDisable(GL_TEXTURE_2D);
				mTexturing = false;
			}
		break;
	};
}

void OGLState::setAlphaBlendingEnabled(const bool isEnabled)
{
	switch (isEnabled) {
		case true:
			if (false == mAlphaBlending) {
				glEnable(GL_BLEND);
				mAlphaBlending = true;
			}
		break;
		case false:
			if (true == mAlphaBlending) {
				glDisable(GL_BLEND);
				mAlphaBlending = false;
			}
		break;
	};
}

void OGLState::setBlendingFunction(const GLenum source, const GLenum destination)
{
	glBlendFunc(source, destination);
}

void OGLState::setFullBlendingFunction(const GLenum sourceRGB, const GLenum destinationRGB
									,const GLenum sourceAlpha, const GLenum destinationAlpha)
{
	glBlendFuncSeparate(sourceRGB, destinationRGB, sourceAlpha, destinationAlpha);
}

void OGLState::addUniformUpdater(const std::string& uniformName, const Resource<ShaderUniformUpdater>& updater)
{
	// should probably check and assert if we already have something for this uniform name.
	mUniformUpdaters[uniformName] = updater;
}

void OGLState::bindShader(const Resource<Shader>& shader)
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

void OGLState::resetAttributes()
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

void OGLState::updateUniforms(const Resource<Material>& material, const Resource<Matrix4>& transform)
{
	std::vector<std::pair<std::string, GLint> > uniforms(mCurrentShader->getUniformArray());
	for (std::vector<std::pair<std::string, GLint> >::iterator itr(uniforms.begin()); itr < uniforms.end(); ++itr)
		mUniformUpdaters[itr->first]->update(itr->second, mCamera, material, transform);
}

void OGLState::updateTextures(const Resource<Material>& material)
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
