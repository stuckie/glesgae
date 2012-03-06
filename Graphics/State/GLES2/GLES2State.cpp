#include "GLES2State.h"



#include "../../Camera.h"
#include "../../Shader.h"
#include "../../ShaderUniformUpdater.h"
#include "../../Material.h"
#include "../../Texture.h"
#include "../../../Maths/Matrix4.h"

using namespace GLESGAE;

#if !defined(GLES1)

const HashString aPositionHS("a_position");
const HashString aColourHS("a_colour");
const HashString aNormalHS("a_normal");
const HashString aTexCoord0HS("a_texCoord0");
const HashString aTexCoord1HS("a_texCoord1");
const HashString aCustom0HS("a_custom0");
const HashString aCustom1HS("a_custom1");
const HashString aCustom2HS("a_custom2");

GLES2State::GLES2State()
: a_position(GL_INVALID_VALUE)
, a_colour(GL_INVALID_VALUE)
, a_normal(GL_INVALID_VALUE)
, a_texCoord0(GL_INVALID_VALUE)
, a_texCoord1(GL_INVALID_VALUE)
, a_custom0(GL_INVALID_VALUE)
, a_custom1(GL_INVALID_VALUE)
, a_custom2(GL_INVALID_VALUE)
, mCamera()
, mTextureMatrix()
, mTexturing(false)
, mAlphaBlending(false)
, mCurrentShader()
, mLastTexture()
, mLastTextureUnit(GL_INVALID_VALUE)
, mUniformUpdaters()
{
}

GLES2State::~GLES2State()
{
}

void GLES2State::setCamera(const Resource<Camera>& camera)
{
	if (mCamera != camera) {
//		glMatrixMode(GL_PROJECTION);
//		glLoadMatrixf(camera->getProjectionMatrix().getData());
		
//		glMatrixMode(GL_MODELVIEW);
		Matrix4& viewMatrix(camera->getViewMatrix());
		viewMatrix(0U, 2U) = -viewMatrix(0U, 2U);
		viewMatrix(1U, 2U) = -viewMatrix(1U, 2U);
		viewMatrix(2U, 2U) = -viewMatrix(2U, 2U);
		viewMatrix(3U, 2U) = -viewMatrix(3U, 2U);
//		glLoadMatrixf(viewMatrix.getData());
		
		mCamera = camera;
	}
}

void GLES2State::setTextureMatrix(const Resource<Matrix4>& matrix)
{
	if (mTextureMatrix != matrix) {
//		glMatrixMode(GL_TEXTURE);
//		glLoadMatrixf(matrix->getData());
		
//		glMatrixMode(GL_MODELVIEW);
		
		mTextureMatrix = matrix;
	}
}

void GLES2State::setTexturingEnabled(const bool isEnabled)
{
	if (true == isEnabled) {
		if (false == mTexturing) {
			glEnable(GL_TEXTURE_2D);
			mTexturing = true;
		}
	} else {
		if (true == mTexturing) {
			glDisable(GL_TEXTURE_2D);
			mTexturing = false;
		}
	}
}

void GLES2State::setAlphaBlendingEnabled(const bool isEnabled)
{
	if (true == isEnabled) {
		if (false == mAlphaBlending) {
			glEnable(GL_BLEND);
			mAlphaBlending = true;
		}
	} else {
		if (true == mAlphaBlending) {
			glDisable(GL_BLEND);
			mAlphaBlending = false;
		}
	}
}

void GLES2State::setBlendingFunction(const GLenum source, const GLenum destination)
{
	glBlendFunc(source, destination);
}

void GLES2State::setFullBlendingFunction(const GLenum sourceRGB, const GLenum destinationRGB
									,const GLenum sourceAlpha, const GLenum destinationAlpha)
{
	glBlendFuncSeparate(sourceRGB, destinationRGB, sourceAlpha, destinationAlpha);
}

void GLES2State::addUniformUpdater(const HashString uniformName, const Resource<ShaderUniformUpdater>& updater)
{
	// should probably check and assert if we already have something for this uniform name.
	mUniformUpdaters[uniformName] = updater;
}

void GLES2State::bindShader(const Resource<Shader>& shader)
{
	if (mCurrentShader != shader) {
		mCurrentShader = shader;
		glUseProgram(shader->getProgramId());
		resetAttributes();
		
		const std::vector<std::pair<HashString, GLint> >& attributes(shader->getAttributeArray());
		for (std::vector<std::pair<HashString, GLint> >::const_iterator itr(attributes.begin()); itr < attributes.end(); ++itr)
			glEnableVertexAttribArray(itr->second);
	}
}

void GLES2State::resetAttributes()
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
		a_position = mCurrentShader->getAttribute(aPositionHS);
		a_colour = mCurrentShader->getAttribute(aColourHS);
		a_normal = mCurrentShader->getAttribute(aNormalHS);
		a_texCoord0 = mCurrentShader->getAttribute(aTexCoord0HS);
		a_texCoord1 = mCurrentShader->getAttribute(aTexCoord1HS);
		a_custom0 = mCurrentShader->getAttribute(aCustom0HS);
		a_custom1 = mCurrentShader->getAttribute(aCustom1HS);
		a_custom2 = mCurrentShader->getAttribute(aCustom2HS);
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

void GLES2State::updateUniforms(const Resource<Material>& material, const Resource<Matrix4>& transform)
{
	std::vector<std::pair<HashString, GLint> > uniforms(mCurrentShader->getUniformArray());
	for (std::vector<std::pair<HashString, GLint> >::iterator itr(uniforms.begin()); itr < uniforms.end(); ++itr)
		mUniformUpdaters[itr->first]->update(itr->second, mCamera, material, transform);
}

void GLES2State::updateTextures(const Resource<Material>& material)
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

#endif // not ES 1

