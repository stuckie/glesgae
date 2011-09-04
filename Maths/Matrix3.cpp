#include "Matrix3.h"

#include <cstring> // for memcpy

using namespace GLESGAE;

Matrix3::Matrix3()
: mMatrix()
{
	setToIdentity();
}

float Matrix3::operator()(const unsigned int row, const unsigned int column) const
{
	return mMatrix[row * 3U + column];
}

float& Matrix3::operator()(const unsigned int row, const unsigned int column)
{
	return mMatrix[row * 3U + column];
}

void Matrix3::setMatrix(const float matrix[9U])
{
	std::memcpy(mMatrix, matrix, sizeof(float) * 9U);
}

void Matrix3::setToIdentity()
{
	//	0	1	2
	//	3	4	5
	//	6	7	8
	mMatrix[1U] = mMatrix[2U] = 0.0F;
	mMatrix[3U] = mMatrix[5U] = 0.0F;
	mMatrix[6U] = mMatrix[7U] = 0.0F;
	mMatrix[0U] = mMatrix[4U] = mMatrix[8U] = 1.0F;
}

void Matrix3::setToZero()
{
	mMatrix[0U] = mMatrix[1U] = mMatrix[2U] = 0.0F;
	mMatrix[3U] = mMatrix[4U] = mMatrix[5U] = 0.0F;
	mMatrix[6U] = mMatrix[7U] = mMatrix[8U] = 0.0F;
}

Vector3 Matrix3::getFrontVector() const
{
	Vector3 vector;
	vector.x() = mMatrix[2U];
	vector.y() = mMatrix[5U];
	vector.z() = mMatrix[8U];
	
	return vector;
}

Vector3 Matrix3::getUpVector() const
{
	Vector3 vector;
	vector.x() = mMatrix[1U];
	vector.y() = mMatrix[4U];
	vector.z() = mMatrix[7U];
	
	return vector;
}

Vector3 Matrix3::getRightVector() const
{
	Vector3 vector;
	vector.x() = mMatrix[0U];
	vector.y() = mMatrix[3U];
	vector.z() = mMatrix[6U];
	
	return vector;
}

void Matrix3::setFrontVector(const Vector3& vector)
{
	mMatrix[2U] = vector.x();
	mMatrix[5U] = vector.y();
	mMatrix[8U] = vector.z();
}

void Matrix3::setUpVector(const Vector3& vector)
{
	mMatrix[1U] = vector.x();
	mMatrix[4U] = vector.y();
	mMatrix[7U] = vector.z();
}

void Matrix3::setRightVector(const Vector3& vector)
{
	mMatrix[0U] = vector.x();
	mMatrix[3U] = vector.y();
	mMatrix[6U] = vector.z();
}

bool Matrix3::operator==(const Matrix3& rhs) const
{
	for (unsigned int index(0U); index < 9U; ++index) {
		if (mMatrix[index] != rhs.mMatrix[index])
			return false;
	}
	
	return true;
}

bool Matrix3::operator!=(const Matrix3& rhs) const
{
	return !(*this == rhs);
}

const Matrix3 Matrix3::operator+(const Matrix3& rhs) const
{
	Matrix3 result(*this);
	result += rhs;
	return result;
}

const Matrix3 Matrix3::operator-(const Matrix3& rhs) const
{
	Matrix3 result(*this);
	result -= rhs;
	return result;
}

const Matrix3 Matrix3::operator*(const Matrix3& rhs) const
{
	Matrix3 result(*this);
	result *= rhs;
	return result;
}

const Matrix3 Matrix3::operator*(const float scalar) const
{
	Matrix3 result(*this);
	result *= scalar;
	return result;
}

const Matrix3 Matrix3::operator/(const float scalar) const
{
	Matrix3 result(*this);
	result /= scalar;
	return result;
}

const Matrix3& Matrix3::operator+=(const Matrix3& rhs)
{
	for (unsigned int index(0U); index < 9U; ++index)
		mMatrix[index] += rhs.mMatrix[index];
		
	return *this;
}

const Matrix3& Matrix3::operator-=(const Matrix3& rhs)
{
	for (unsigned int index(0U); index < 9U; ++index)
		mMatrix[index] -= rhs.mMatrix[index];
	
	return *this;
}

const Matrix3& Matrix3::operator*=(const Matrix3& rhs)
{
	float newElement(0.0F);
	for (unsigned int row(0U); row < 3U; ++row) {
		for (unsigned int column(0U); column < 3U; ++column) {
			newElement = 0.0F;
			for (unsigned int index(0U); index < 3U; ++index)
				newElement += mMatrix[row * 3U + index] * rhs.mMatrix[index * 3U + column];
			(*this)(row, column) = newElement;
		}
	}
	return *this;
}

const Matrix3& Matrix3::operator*=(const float scalar)
{
	for (unsigned int index(0U); index < 9U; ++index)
		mMatrix[index] *= scalar;
		
	return *this;
}

const Matrix3& Matrix3::operator/=(const float scalar)
{
	const float inverse(1.0F / scalar);
	for (unsigned int index(0U); index < 9U; ++index)
		mMatrix[index] *= inverse;
		
	return *this;
}

