#include "Matrix4.h"

#include <cstring> // for memcpy

#pragma GCC diagnostic ignored "-Wstrict-overflow"

using namespace GLESGAE;

Matrix4::Matrix4()
: mMatrix()
{
	setToIdentity();
}

float Matrix4::operator()(const unsigned int row, const unsigned int column) const
{
	return mMatrix[row * 4U + column];
}

float& Matrix4::operator()(const unsigned int row, const unsigned int column)
{
	return mMatrix[row * 4U + column];
}

float Matrix4::operator[](const unsigned int index) const
{
	return mMatrix[index];
}

float& Matrix4::operator[](const unsigned int index)
{
	return mMatrix[index];
}

void Matrix4::setMatrix(const float matrix[16U])
{
	std::memcpy(mMatrix, matrix, sizeof(float) * 16U);
}

void Matrix4::setToIdentity()
{
	//	0	1	2	3
	//	4	5	6	7
	//	8	9	10	11
	//	12	13	14	15
	mMatrix[1U] = mMatrix[2U] = mMatrix[3U] = 0.0F;
	mMatrix[4U] = mMatrix[6U] = mMatrix[7U] = 0.0F;
	mMatrix[8U] = mMatrix[9U] = mMatrix[11U] = 0.0F;
	mMatrix[12U] = mMatrix[13U] = mMatrix[14U] = 0.0F;
	mMatrix[0U] = mMatrix[5U] = mMatrix[10U] = mMatrix[15U] = 1.0F;
}

void Matrix4::setToZero()
{
	mMatrix[0U] = mMatrix[1U] = mMatrix[2U] = mMatrix[3U] = 0.0F;
	mMatrix[4U] = mMatrix[5U] = mMatrix[6U] = mMatrix[7U] = 0.0F;
	mMatrix[8U] = mMatrix[9U] = mMatrix[10U] = mMatrix[11U] = 0.0F;
	mMatrix[12U] = mMatrix[13U] = mMatrix[14U] = mMatrix[15U] = 0.0F;
}

Matrix4 Matrix4::getTranspose() const
{
	Matrix4 transpose;
	for (unsigned int row(0U); row < 4U; ++row) {
		for (unsigned int column(0U); column < 4U; ++column)
			transpose(row, column) = (*this)(column, row);
	}
	
	return transpose;
}

void Matrix4::decompose(Matrix3* rotation, Vector3* position) const
{
	getPosition(position);
	getRotation(rotation);
}

void Matrix4::compose(const Matrix3& rotation, const Vector3& position)
{
	setPosition(position);
	setRotation(rotation);
}

void Matrix4::setPosition(const Vector3& position)
{
	(*this)(0U, 3U) = position.x();
	(*this)(1U, 3U) = position.y();
	(*this)(2U, 3U) = position.z();
}

void Matrix4::setRotation(const Matrix3& rotation)
{
	for (unsigned int row(0U); row < 3U; ++row) {
		for (unsigned int column(0U); column < 3U; ++column)
			(*this)(row, column) = rotation(row, column);
	}
}

void Matrix4::getPosition(Vector3* position) const
{
	position->x() = (*this)(0U, 3U);
	position->y() = (*this)(1U, 3U);
	position->z() = (*this)(2U, 3U);
}

void Matrix4::getRotation(Matrix3* rotation) const
{
	for (unsigned int row(0U); row < 3U; ++row) {
		for (unsigned int column(0U); column < 3U; ++column)
			(*rotation)(row, column) = (*this)(row, column);
	}
}

void Matrix4::setScale(const Vector3& scale)
{
	(*this)(0U, 0U) *= scale.x();
	(*this)(1U, 1U) *= scale.y();
	(*this)(2U, 2U) *= scale.z();
}

bool Matrix4::operator==(const Matrix4& rhs) const
{
	for (unsigned int index(0U); index < 16U; ++index) {
		if (mMatrix[index] != rhs.mMatrix[index])
			return false;
	}
	
	return true;
}

bool Matrix4::operator!=(const Matrix4& rhs) const
{
	return !(*this == rhs);
}

const Matrix4 Matrix4::operator+(const Matrix4& rhs) const
{
	Matrix4 result(*this);
	result += rhs;
	return result;
}

const Matrix4 Matrix4::operator-(const Matrix4& rhs) const
{
	Matrix4 result(*this);
	result -= rhs;
	return result;
}

const Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
	Matrix4 result(*this);
	result *= rhs;
	return result;
}

const Matrix4 Matrix4::operator*(const float scalar) const
{
	Matrix4 result(*this);
	result *= scalar;
	return result;
}

const Matrix4 Matrix4::operator/(const float scalar) const
{
	Matrix4 result(*this);
	result /= scalar;
	return result;
}

const Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
	for (unsigned int index(0U); index < 16U; ++index)
		mMatrix[index] += rhs.mMatrix[index];
		
	return *this;
}

const Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
	for (unsigned int index(0U); index < 16U; ++index)
		mMatrix[index] -= rhs.mMatrix[index];
	
	return *this;
}

#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
#pragma GCC push_options
#pragma GCC optimize ("O1")
#endif
const Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
	float newElement(0.0F);
	for (unsigned int row(0U); row < 4U; ++row) {
		for (unsigned int column(0U); column < 4U; ++column) {
			newElement = 0.0F;
			for (unsigned int index(0U); index < 4U; ++index)
				newElement += mMatrix[row * 4U + index] * rhs.mMatrix[index * 4U + column]; // Seems to cause a "possible" overflow on -O2 and -O3... which I think is bogus.
			(*this)(row, column) = newElement;
		}
	}
	return *this;
}
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
#pragma GCC pop_options
#endif

const Matrix4& Matrix4::operator*=(const float scalar)
{
	for (unsigned int index(0U); index < 16U; ++index)
		mMatrix[index] *= scalar;
		
	return *this;
}

const Matrix4& Matrix4::operator/=(const float scalar)
{
	const float inverse(1.0F / scalar);
	for (unsigned int index(0U); index < 16U; ++index)
		mMatrix[index] *= inverse;
		
	return *this;
}

