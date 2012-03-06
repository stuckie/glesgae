#include "FixedFunctionGlVARenderer.h"

#if defined(LINUX)
	#include "../../Context/Linux/GLee.h"
#elif defined(PANDORA)
	#if defined(GLES1)
		#include <GLES/gl.h>
	#endif
#endif

#include "../../Camera.h"
#include "../../IndexBuffer.h"
#include "../../Material.h"
#include "../../Mesh.h"
#include "../../Texture.h"
#include "../../VertexBuffer.h"
#include "../../../Maths/Matrix4.h"
#include "../../../Resources/Resource.h"

using namespace GLESGAE;

FixedFunctionGlVARenderer::FixedFunctionGlVARenderer()
: mFixedFunctionTexUnits()
, mFixedFunctionLastTexUnit(0U)
, mLastVertexBuffer(0)
, mLastTexture(0)
{
	// Mark all texture co-ordinate arrays as offline.
	for (unsigned int index(0U); index < 8U; ++index)
		mFixedFunctionTexUnits[index] = false;
}

void FixedFunctionGlVARenderer::drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform)
{
	const Resource<IndexBuffer>& indexBuffer(mesh->getIndexBuffer());
	const Resource<VertexBuffer>& vertexBuffer(mesh->getVertexBuffer());
	const Resource<Material>& material(mesh->getMaterial());
	unsigned int currentTextureUnit(0U);

	if (mLastVertexBuffer != vertexBuffer) {
		mLastVertexBuffer = vertexBuffer;
		const VertexBuffer::Format* meshFormat(vertexBuffer->getFormat());
		for (unsigned int index(0U); index < VertexBuffer::FORMAT_SIZE; ++index) {
			const VertexBuffer::Format* itr(&meshFormat[index]);
			switch (itr->getType()) {
				// Position
				case VertexBuffer::FORMAT_POSITION_2F:
					glVertexPointer(2, GL_FLOAT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_POSITION_3F:
					glVertexPointer(3, GL_FLOAT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_POSITION_4F:
					glVertexPointer(4, GL_FLOAT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_POSITION_2S:
					glVertexPointer(2, GL_SHORT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_POSITION_3S:
					glVertexPointer(3, GL_SHORT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_POSITION_4S:
					glVertexPointer(4, GL_SHORT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_POSITION_2B:
					glVertexPointer(2, GL_BYTE, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_POSITION_3B:
					glVertexPointer(3, GL_BYTE, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_POSITION_4B:
					glVertexPointer(4, GL_BYTE, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				// Normal
				case VertexBuffer::FORMAT_NORMAL_3F:
					glNormalPointer(GL_FLOAT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_NORMAL_3S:
					glNormalPointer(GL_SHORT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_NORMAL_3B:
					glNormalPointer(GL_BYTE, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				// Colour
				case VertexBuffer::FORMAT_COLOUR_4F:
					glColorPointer(4, GL_FLOAT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_COLOUR_3F:
					glColorPointer(3, GL_FLOAT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_COLOUR_4S:
					glColorPointer(4, GL_SHORT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_COLOUR_3S:
					glColorPointer(3, GL_SHORT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_COLOUR_4UB:
					glColorPointer(4, GL_UNSIGNED_BYTE, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_COLOUR_3UB:
					glColorPointer(3, GL_UNSIGNED_BYTE, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				// Textures and Co-ordinates
				case VertexBuffer::FORMAT_TEXTURE_2F:
					setupTexturing(&currentTextureUnit, material);
					glTexCoordPointer(2, GL_FLOAT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_TEXTURE_3F:
					setupTexturing(&currentTextureUnit, material);
					glTexCoordPointer(3, GL_FLOAT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_TEXTURE_4F:
					setupTexturing(&currentTextureUnit, material);
					glTexCoordPointer(4, GL_FLOAT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_TEXTURE_2S:
					setupTexturing(&currentTextureUnit, material);
					glTexCoordPointer(2, GL_SHORT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_TEXTURE_3S:
					setupTexturing(&currentTextureUnit, material);
					glTexCoordPointer(3, GL_SHORT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_TEXTURE_4S:
					setupTexturing(&currentTextureUnit, material);
					glTexCoordPointer(4, GL_SHORT, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_TEXTURE_2B:
					setupTexturing(&currentTextureUnit, material);
					glTexCoordPointer(2, GL_BYTE, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_TEXTURE_3B:
					setupTexturing(&currentTextureUnit, material);
					glTexCoordPointer(3, GL_BYTE, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				case VertexBuffer::FORMAT_TEXTURE_4B:
					setupTexturing(&currentTextureUnit, material);
					glTexCoordPointer(4, GL_BYTE, 0, vertexBuffer->getData() + itr->getOffset());
					break;
				default:
					break;
			};
		}
	disableTexturing(currentTextureUnit);	// Disable any excess texture units
	}

	glPushMatrix();
	glMultMatrixf(transform->getTranspose().getData());

	switch (indexBuffer->getType()) {
		case IndexBuffer::INDEX_FLOAT:
			glDrawElements(GL_TRIANGLES, indexBuffer->getSize(), GL_FLOAT, indexBuffer->getData());
			break;
		case IndexBuffer::INDEX_UNSIGNED_BYTE:
			glDrawElements(GL_TRIANGLES, indexBuffer->getSize(), GL_UNSIGNED_BYTE, indexBuffer->getData());
			break;
		case IndexBuffer::INDEX_UNSIGNED_SHORT:
			glDrawElements(GL_TRIANGLES, indexBuffer->getSize(), GL_UNSIGNED_SHORT, indexBuffer->getData());
			break;
		default:
			break;
	};
	mFixedFunctionLastTexUnit = currentTextureUnit;
	
	glPopMatrix();
}

void FixedFunctionGlVARenderer::setupTexturing(unsigned int* textureUnit, const Resource<Material>& material)
{
	if (false == mFixedFunctionTexUnits[*textureUnit]) { // This texture unit isn't currently enabled
		mFixedFunctionTexUnits[*textureUnit] = true;
		glClientActiveTexture(GL_TEXTURE0 + *textureUnit);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	} else {
		if (*textureUnit != mFixedFunctionLastTexUnit) // This texture unit is enabled but it's not the current one
			glActiveTexture(GL_TEXTURE0 + *textureUnit);
	}

	const Resource<Texture>& texture(material->getTexture(*textureUnit));
	if ((texture != 0) && (mLastTexture != texture)) {
		mLastTexture = texture;
		glBindTexture(GL_TEXTURE_2D, texture->getId());
	}

	mFixedFunctionLastTexUnit = (*textureUnit);
	++(*textureUnit);
}

void FixedFunctionGlVARenderer::disableTexturing(const unsigned int currentTextureUnit)
{
	unsigned int delta(mFixedFunctionLastTexUnit);
	while (delta > currentTextureUnit) { // We're using less texture units than we need
		glClientActiveTexture(GL_TEXTURE0 + delta);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		--delta;
	}
}
