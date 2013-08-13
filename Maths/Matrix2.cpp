#include "Matrix2.h"

#include <cstring> // for memcpy

using namespace GLESGAE;

Matrix2::Matrix2()
: mMatrix()
{
	setToIdentity();
}

float Matrix2::operator()(const unsigned int row, const unsigned int column) const
{
	return mMatrix[row * 2U + column];
}

float& Matrix2::operator()(const unsigned int row, const unsigned int column)
{
	return mMatrix[row * 2U + column];
}

void Matrix2::setMatrix(const float matrix[4U])
{
	std::memcpy(mMatrix, matrix, sizeof(float) * 4U);
}

void Matrix2::setToIdentity()
{
	//	0	1
	//	2	3
	mMatrix[1U] = mMatrix[2U] = 0.0F;
	mMatrix[0U] = mMatrix[3U] = 1.0F;
}

void Matrix2::setToZero()
{
	mMatrix[0U] = mMatrix[1U] = 0.0F;
	mMatrix[2U] = mMatrix[3U] = 0.0F;
}

bool Matrix2::operator==(const Matrix2& rhs) const
{
	for (unsigned int index(0U); index < 4U; ++index) {
		if (mMatrix[index] != rhs.mMatrix[index])
			return false;
	}
	
	return true;
}

bool Matrix2::operator!=(const Matrix2& rhs) const
{
	return !(*this == rhs);
}

Matrix2 Matrix2::operator+(const Matrix2& rhs) const
{
	Matrix2 result(*this);
	result += rhs;
	return result;
}

Matrix2 Matrix2::operator-(const Matrix2& rhs) const
{
	Matrix2 result(*this);
	result -= rhs;
	return result;
}

Matrix2 Matrix2::operator*(const Matrix2& rhs) const
{
	Matrix2 result(*this);
	result *= rhs;
	return result;
}

Matrix2 Matrix2::operator*(const float scalar) const
{
	Matrix2 result(*this);
	result *= scalar;
	return result;
}

Matrix2 Matrix2::operator/(const float scalar) const
{
	Matrix2 result(*this);
	result /= scalar;
	return result;
}

const Matrix2& Matrix2::operator+=(const Matrix2& rhs)
{
	for (unsigned int index(0U); index < 4U; ++index)
		mMatrix[index] += rhs.mMatrix[index];
		
	return *this;
}

const Matrix2& Matrix2::operator-=(const Matrix2& rhs)
{
	for (unsigned int index(0U); index < 4U; ++index)
		mMatrix[index] -= rhs.mMatrix[index];
	
	return *this;
}

const Matrix2& Matrix2::operator*=(const Matrix2& rhs)
{
	float newElement(0.0F);
	for (unsigned int row(0U); row < 2U; ++row) {
		for (unsigned int column(0U); column < 2U; ++column) {
			newElement = 0.0F;
			for (unsigned int index(0U); index < 2U; ++index)
				newElement += mMatrix[row * 2U + index] * rhs.mMatrix[index * 2U + column];
			(*this)(row, column) = newElement;
		}
	}
	return *this;
}

const Matrix2& Matrix2::operator*=(const float scalar)
{
	for (unsigned int index(0U); index < 4U; ++index)
		mMatrix[index] *= scalar;
		
	return *this;
}

const Matrix2& Matrix2::operator/=(const float scalar)
{
	const float inverse(1.0F / scalar);
	for (unsigned int index(0U); index < 4U; ++index)
		mMatrix[index] *= inverse;
		
	return *this;
}

