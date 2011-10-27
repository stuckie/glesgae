#include "GLES1State.h"

#include "../../Camera.h"
#include "../../../Maths/Matrix4.h"

#include <cstdio>

using namespace GLESGAE;

GLES1State::GLES1State()
: mCamera()
, mTextureMatrix()
, mTexturing(false)
, mAlphaBlending(false)
, mVertexPositions(false)
, mVertexColours(false)
, mVertexNormals(false)
{
}

GLES1State::~GLES1State()
{
}

void GLES1State::setCamera(const Resource<Camera>& camera)
{
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

void GLES1State::setTextureMatrix(const Resource<Matrix4>& matrix)
{
	if (mTextureMatrix != matrix) {
		glMatrixMode(GL_TEXTURE);
		glLoadMatrixf(matrix->getData());
		
		glMatrixMode(GL_MODELVIEW);
		
		mTextureMatrix = matrix;
	}
}

void GLES1State::setTexturingEnabled(const bool isEnabled)
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

void GLES1State::setAlphaBlendingEnabled(const bool isEnabled)
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

void GLES1State::setVertexPositionsEnabled(const bool isEnabled)
{
	switch (isEnabled) {
		case true:
			if (false == mVertexPositions) {
				glEnableClientState(GL_VERTEX_ARRAY);
				mVertexPositions = true;
			}
		break;
		case false:
			if (true == mVertexPositions) {
				glDisableClientState(GL_VERTEX_ARRAY);
				mVertexPositions = false;
			}
		break;
	};
}

void GLES1State::setVertexColoursEnabled(const bool isEnabled)
{
	switch (isEnabled) {
		case true:
			if (false == mVertexColours) {
				glEnableClientState(GL_COLOR_ARRAY);
				mVertexColours = true;
			}
		break;
		case false:
			if (true == mVertexColours) {
				glDisableClientState(GL_COLOR_ARRAY);
				mVertexColours = false;
			}
		break;
	};
}

void GLES1State::setVertexNormalsEnabled(const bool isEnabled)
{
	switch (isEnabled) {
		case true:
			if (false == mVertexNormals) {
				glEnableClientState(GL_NORMAL_ARRAY);
				mVertexNormals = true;
			}
		break;
		case false:
			if (true == mVertexNormals) {
				glDisableClientState(GL_NORMAL_ARRAY);
				mVertexNormals = false;
			}
		break;
	};
}

void GLES1State::setBlendingFunction(const GLenum source, const GLenum destination)
{
	glBlendFunc(source, destination);
}

void GLES1State::setFullBlendingFunction(const GLenum sourceRGB, const GLenum destinationRGB
									,const GLenum sourceAlpha, const GLenum destinationAlpha)
{
	glBlendFuncSeparate(sourceRGB, destinationRGB, sourceAlpha, destinationAlpha);
}

