#include "GLES1State.h"

#include "../../Camera.h"
#include "../../../Maths/Matrix4.h"

#include <cstdio>
#include <cassert>

using namespace GLESGAE;

GLES1State::GLES1State()
: mCamera(0)
, mTextureMatrix(0)
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

void GLES1State::setCamera(Camera* const camera)
{
	assert(0 != camera);
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

void GLES1State::setTextureMatrix(Matrix4* const matrix)
{
	assert(0 != matrix);
	if (mTextureMatrix != matrix) {
		glMatrixMode(GL_TEXTURE);
		glLoadMatrixf(matrix->getData());
		
		glMatrixMode(GL_MODELVIEW);
		
		mTextureMatrix = matrix;
	}
}

void GLES1State::setTexturingEnabled(const bool isEnabled)
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

void GLES1State::setAlphaBlendingEnabled(const bool isEnabled)
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

void GLES1State::setVertexPositionsEnabled(const bool isEnabled)
{
	if (true == isEnabled) {
		if (false == mVertexPositions) {
			glEnableClientState(GL_VERTEX_ARRAY);
			mVertexPositions = true;
		}
	} else {
		if (true == mVertexPositions) {
			glDisableClientState(GL_VERTEX_ARRAY);
			mVertexPositions = false;
		}
	}
}

void GLES1State::setVertexColoursEnabled(const bool isEnabled)
{
	if (true == isEnabled) {
		if (false == mVertexColours) {
			glEnableClientState(GL_COLOR_ARRAY);
			mVertexColours = true;
		}
	} else {
		if (true == mVertexColours) {
			glDisableClientState(GL_COLOR_ARRAY);
			mVertexColours = false;
		}
	}
}

void GLES1State::setVertexNormalsEnabled(const bool isEnabled)
{
	if (true == isEnabled) {
		if (false == mVertexNormals) {
			glEnableClientState(GL_NORMAL_ARRAY);
			mVertexNormals = true;
		}
	} else {
		if (true == mVertexNormals) {
			glDisableClientState(GL_NORMAL_ARRAY);
			mVertexNormals = false;
		}
	}
}

void GLES1State::setBlendingFunction(const GLenum source, const GLenum destination)
{
	glBlendFunc(source, destination);
}

