#include "Sprite.h"

#include "../Maths/Matrix4.h"
#include "../Maths/Matrix3.h"
#include "../Maths/Vector2.h"
#include "../Maths/Vector3.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Material.h"

#include <cmath>

using namespace GLESGAE;

Sprite::Sprite(Material* const material, const Vector2& size, const float u, const float v, const float s, const float t)
: mMesh()
, mTransform(new Matrix4)
, mPosition(0.0F, 0.0F)
, mRotation(0.0F)
{
	float vertexData[24] = {// Position - 16 floats
					-1.0F * size.x(), 1.0F * size.y(), 0.0F, 1.0F,
					1.0F * size.x(), 1.0F * size.y(), 0.0F, 1.0F,
					1.0F * size.x(), -1.0F * size.y(), 0.0F, 1.0F,
					-1.0F * size.x(), -1.0F * size.y(), 0.0F, 1.0F,
					// Tex Coords - 8 floats
					u, v, 	// bottom left
					s, v, 	// top left
					s, t, 	// top right
					u, t};	// bottom right

	unsigned int vertexSize = 24 * sizeof(float);

	unsigned char indexData[6] = { 0, 1, 2, 2, 3, 0 };
	unsigned int indexSize = 6 * sizeof(unsigned char);

	VertexBuffer* newVertexBuffer(new VertexBuffer(reinterpret_cast<unsigned char*>(&vertexData), vertexSize));
	newVertexBuffer->addFormatIdentifier(VertexBuffer::FORMAT_POSITION_4F, 4U);
	newVertexBuffer->addFormatIdentifier(VertexBuffer::FORMAT_TEXTURE_2F, 4U);
	
	IndexBuffer* newIndexBuffer(new IndexBuffer(reinterpret_cast<unsigned char*>(&indexData), indexSize, IndexBuffer::INDEX_UNSIGNED_BYTE, IndexBuffer::FORMAT_TRIANGLES));
	
	mMesh = new Mesh(newVertexBuffer, newIndexBuffer, material);
}

Sprite::Sprite(const Sprite& sprite)
: mMesh(sprite.mMesh)
, mTransform(sprite.mTransform)
, mPosition(sprite.mPosition)
, mRotation(sprite.mRotation)
{
}

Sprite& Sprite::operator=(const Sprite& sprite)
{
	if (this != &sprite) {
		delete mMesh;
		delete mTransform;
		mMesh = sprite.mMesh;
		mTransform = sprite.mTransform;
		mPosition = sprite.mPosition;
		mRotation = sprite.mRotation;
	}
	
	return *this;
}

Sprite::~Sprite()
{
}

Mesh* Sprite::getMesh() const
{
	return mMesh;
}

Matrix4* Sprite::getTransform() const
{
	return mTransform;
}

const Vector2& Sprite::getPosition() const
{
	return mPosition;
}

float Sprite::getRotation() const
{
	return mRotation;
}

void Sprite::setPosition(const Vector2& position)
{
	mPosition = position;
	mTransform->setPosition(Vector3(position.x(), position.y(), 0.0F));
}

void Sprite::setRotation(const float angle)
{
	mRotation = angle;
	Matrix3 rotation;
	mTransform->getRotation(&rotation);
		rotation(0, 0) = cosf(angle);
		rotation(0, 1) = sinf(angle);
		rotation(1, 0) = -sinf(angle);
		rotation(1, 1) = cosf(angle);
	mTransform->setRotation(rotation);
}

