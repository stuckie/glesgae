#ifndef GLES2 // GLES2 does not support any of this

#include "FixedFunctionContext.h"

#include "../Camera.h"
#include "../IndexBuffer.h"
#include "../Material.h"
#include "../Mesh.h"
#include "../Texture.h"
#include "../VertexBuffer.h"
#include "../../Maths/Matrix4.h"
#include "../../Resources/Resource.h"

using namespace GLESGAE;

FixedFunctionContext::FixedFunctionContext()
: mFixedFunctionTexUnits()
, mFixedFunctionLastTexUnit(0U)
, mCamera()
, mLastVertexBuffer()
, mLastIndexBuffer()
, mLastTexture()
{
	// Mark all texture co-ordinate arrays as offline.
	for (unsigned int index(0U); index < 8U; ++index)
		mFixedFunctionTexUnits[index] = false;
}

FixedFunctionContext::~FixedFunctionContext()
{
}

void FixedFunctionContext::drawMeshFixedFunction(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform)
{
	const Resource<IndexBuffer>& indexBuffer(mesh->getIndexBuffer());
	const Resource<VertexBuffer>& vertexBuffer(mesh->getVertexBuffer());
	const Resource<Material>& material(mesh->getMaterial());
	unsigned int currentTextureUnit(0U);

	const bool newBuffer(!(mLastVertexBuffer == vertexBuffer));
	if (true == newBuffer) {
		mLastVertexBuffer = vertexBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->getVboId());
	}
	
	const std::vector<VertexBuffer::Format>& meshFormat(vertexBuffer->getFormat());
	for (std::vector<VertexBuffer::Format>::const_iterator itr(meshFormat.begin()); itr < meshFormat.end(); ++itr) {
		switch (itr->getType()) {
			// Position
			case VertexBuffer::FORMAT_POSITION_2F:
				if (true == newBuffer)
					glVertexPointer(2, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_POSITION_3F:
				if (true == newBuffer)
					glVertexPointer(3, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_POSITION_4F:
				if (true == newBuffer)
					glVertexPointer(4, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_POSITION_2S:
				if (true == newBuffer)
					glVertexPointer(2, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_POSITION_3S:
				if (true == newBuffer)
					glVertexPointer(3, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_POSITION_4S:
				if (true == newBuffer)
					glVertexPointer(4, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_POSITION_2B:
				if (true == newBuffer)
					glVertexPointer(2, GL_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_POSITION_3B:
				if (true == newBuffer)
					glVertexPointer(3, GL_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_POSITION_4B:
				if (true == newBuffer)
					glVertexPointer(4, GL_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			// Normal
			case VertexBuffer::FORMAT_NORMAL_3F:
				if (true == newBuffer)
					glNormalPointer(GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_NORMAL_3S:
				if (true == newBuffer)
					glNormalPointer(GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_NORMAL_3B:
				if (true == newBuffer)
					glNormalPointer(GL_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			// Colour
			case VertexBuffer::FORMAT_COLOUR_4F:
				if (true == newBuffer)
					glColorPointer(4, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_COLOUR_3F:
				if (true == newBuffer)
					glColorPointer(3, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_COLOUR_4S:
				if (true == newBuffer)
					glColorPointer(4, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_COLOUR_3S:
				if (true == newBuffer)
					glColorPointer(3, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_COLOUR_4UB:
				if (true == newBuffer)
					glColorPointer(4, GL_UNSIGNED_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_COLOUR_3UB:
				if (true == newBuffer)
					glColorPointer(3, GL_UNSIGNED_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			// Textures and Co-ordinates
			case VertexBuffer::FORMAT_TEXTURE_2F:
				setupFixedFunctionTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(2, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_3F:
				setupFixedFunctionTexturing(&currentTextureUnit, material);
				if (true == newBuffer)						
					glTexCoordPointer(3, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_4F:
				setupFixedFunctionTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(4, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_2S:
				setupFixedFunctionTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(2, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_3S:
				setupFixedFunctionTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(3, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_4S:
				setupFixedFunctionTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(4, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_2B:
				setupFixedFunctionTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(2, GL_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_3B:
				setupFixedFunctionTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(3, GL_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_4B:
				setupFixedFunctionTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(4, GL_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			default:
				break;
		};
	}
	
	if (mLastIndexBuffer != indexBuffer) {
		mLastIndexBuffer = indexBuffer;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getVboId());
	}
	
	glPushMatrix();
	glMultMatrixf(transform->getTranspose().getData());

	disableFixedFunctionTexturing(currentTextureUnit);	// Disable any excess texture units
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
	
	glPopMatrix();
}

void FixedFunctionContext::enableFixedFunctionVertexPositions()
{
	glEnableClientState(GL_VERTEX_ARRAY);
}

void FixedFunctionContext::disableFixedFunctionVertexPositions()
{
	glDisableClientState(GL_VERTEX_ARRAY);
}

void FixedFunctionContext::enableFixedFunctionVertexColours()
{
	glEnableClientState(GL_COLOR_ARRAY);
}

void FixedFunctionContext::disableFixedFunctionVertexColours()
{
	glDisableClientState(GL_COLOR_ARRAY);
}

void FixedFunctionContext::enableFixedFunctionVertexNormals()
{
	glEnableClientState(GL_NORMAL_ARRAY);
}

void FixedFunctionContext::disableFixedFunctionVertexNormals()
{
	glDisableClientState(GL_NORMAL_ARRAY);
}

void FixedFunctionContext::enableFixedFunctionBlending()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void FixedFunctionContext::disableFixedFunctionBlending()
{
	glDisable(GL_BLEND);
}

void FixedFunctionContext::setFixedFunctionCamera(const Resource<Camera>& camera)
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

void FixedFunctionContext::setFixedFunctionTextureMatrix(const Resource<Matrix4>& matrix)
{
	glMatrixMode(GL_TEXTURE);
	glLoadMatrixf(matrix->getData());
	
	glMatrixMode(GL_MODELVIEW);
}

void FixedFunctionContext::setupFixedFunctionTexturing(unsigned int* textureUnit, const Resource<Material>& material)
{
	if (false == mFixedFunctionTexUnits[*textureUnit]) { // This texture unit isn't currently enabled
		mFixedFunctionTexUnits[*textureUnit] = true;
		glClientActiveTexture(GL_TEXTURE0 + *textureUnit);
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	} else {
		if (*textureUnit != mFixedFunctionLastTexUnit) { // This texture unit is enabled but it's not the current one
			glActiveTexture(GL_TEXTURE0 + *textureUnit);
		}
	}

	const Resource<Texture>& texture(material->getTexture(*textureUnit));
	if (mLastTexture != texture) {
		mLastTexture = texture;
		glBindTexture(GL_TEXTURE_2D, texture->getId());
	}

	mFixedFunctionLastTexUnit = (*textureUnit);
	++(*textureUnit);
}

void FixedFunctionContext::disableFixedFunctionTexturing(const unsigned int currentTextureUnit)
{
	unsigned int delta(mFixedFunctionLastTexUnit);
	while (delta > currentTextureUnit) { // We're using less texture units than we need
		glClientActiveTexture(GL_TEXTURE0 + delta);
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		--delta;
	}
}

#endif
