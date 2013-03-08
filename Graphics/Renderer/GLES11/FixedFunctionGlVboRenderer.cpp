#include "FixedFunctionGlVboRenderer.h"

#if defined(LINUX)
	#include "../../Context/Linux/GLee.h"
#elif defined(PANDORA) || defined(ANDROID)
	#include <GLES/gl.h>
#endif

#include "../../Camera.h"
#include "../../IndexBuffer.h"
#include "../../Material.h"
#include "../../Mesh.h"
#include "../../Texture.h"
#include "../../VertexBuffer.h"
#include "../../../Maths/Matrix4.h"

using namespace GLESGAE;

FixedFunctionGlVboRenderer::FixedFunctionGlVboRenderer()
: mFixedFunctionTexUnits()
, mFixedFunctionLastTexUnit(0U)
, mLastVertexBuffer()
, mLastIndexBuffer()
, mLastTexture()
{
	// Mark all texture co-ordinate arrays as offline.
	for (unsigned int index(0U); index < 8U; ++index)
		mFixedFunctionTexUnits[index] = false;
}

FixedFunctionGlVboRenderer::~FixedFunctionGlVboRenderer()
{
}

void FixedFunctionGlVboRenderer::drawMesh(Mesh* const mesh, Matrix4* const transform)
{
	IndexBuffer* const indexBuffer(mesh->getIndexBuffer());
	VertexBuffer* const vertexBuffer(mesh->getVertexBuffer());
	Material* const material(mesh->getMaterial());
	unsigned int currentTextureUnit(0U);

	const bool newBuffer(!(mLastVertexBuffer == vertexBuffer));
	if (true == newBuffer) {
		mLastVertexBuffer = vertexBuffer;
		if (0 == vertexBuffer->getVboId()) { // TODO: This needs redone to store all VboIds internally
			GLuint* buffer(new GLuint);
			glGenBuffers(1, buffer);
			vertexBuffer->setVboId(buffer);
			glBindBuffer(GL_ARRAY_BUFFER, *buffer);
			glBufferData(GL_ARRAY_BUFFER, vertexBuffer->getSize(), vertexBuffer->getData(), GL_STATIC_DRAW);
		}
		else
			glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer->getVboId());
	}
	
	const VertexBuffer::Format* meshFormat(vertexBuffer->getFormat());
	for (unsigned int index(0U); index < VertexBuffer::FORMAT_SIZE; ++index) {
		const VertexBuffer::Format* itr(&meshFormat[index]);
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
				setupTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(2, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_3F:
				setupTexturing(&currentTextureUnit, material);
				if (true == newBuffer)						
					glTexCoordPointer(3, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_4F:
				setupTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(4, GL_FLOAT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_2S:
				setupTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(2, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_3S:
				setupTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(3, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_4S:
				setupTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(4, GL_SHORT, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_2B:
				setupTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(2, GL_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_3B:
				setupTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(3, GL_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			case VertexBuffer::FORMAT_TEXTURE_4B:
				setupTexturing(&currentTextureUnit, material);
				if (true == newBuffer)
					glTexCoordPointer(4, GL_BYTE, 0, reinterpret_cast<char*>(itr->getOffset()));
				break;
			default:
				break;
		};
	}

	if (mLastIndexBuffer != indexBuffer) {
		mLastIndexBuffer = indexBuffer;
		if (0 == indexBuffer->getVboId()) { // TODO: This needs redone to store all VboIds internally
			GLuint* buffer(new GLuint);
			glGenBuffers(1, buffer);
			indexBuffer->setVboId(buffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getSize(), indexBuffer->getData(), GL_STATIC_DRAW);
		}
		else
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBuffer->getVboId());
	}
	
	glPushMatrix();
	glMultMatrixf(transform->getTranspose().getData());

	disableTexturing(currentTextureUnit);	// Disable any excess texture units
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
	
	glPopMatrix();
}

void FixedFunctionGlVboRenderer::setupTexturing(unsigned int* textureUnit, Material* const material)
{
	if (false == mFixedFunctionTexUnits[*textureUnit]) { // This texture unit isn't currently enabled
		mFixedFunctionTexUnits[*textureUnit] = true;
		glClientActiveTexture(GL_TEXTURE0 + *textureUnit);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	} else {
		if (*textureUnit != mFixedFunctionLastTexUnit) // This texture unit is enabled but it's not the current one
			glActiveTexture(GL_TEXTURE0 + *textureUnit);
	}

	Texture* const texture(material->getTexture(*textureUnit));
	if (mLastTexture != texture) {
		mLastTexture = texture;
		glBindTexture(GL_TEXTURE_2D, texture->getId());
	}

	mFixedFunctionLastTexUnit = (*textureUnit);
	++(*textureUnit);
}

void FixedFunctionGlVboRenderer::disableTexturing(const unsigned int currentTextureUnit)
{
	unsigned int delta(mFixedFunctionLastTexUnit);
	while (delta > currentTextureUnit) { // We're using less texture units than we need
		glClientActiveTexture(GL_TEXTURE0 + delta);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		--delta;
	}
}

