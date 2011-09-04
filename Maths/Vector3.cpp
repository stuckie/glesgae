#include "Vector3.h"

#include <cmath>

using namespace GLESGAE;

Vector3::Vector3()
: mVector()
{
	setToZero();
}

Vector3::Vector3(const float x, const float y, const float z)
: mVector()
{
	mVector[0U] = x;
	mVector[1U] = y;
	mVector[2U] = z;
}

bool Vector3::operator==(const Vector3& rhs) const
{
	return (((*this)(0U) == rhs(0U))
		&&	((*this)(1U) == rhs(1U))
		&&	((*this)(2U) == rhs(2U)));
}

bool Vector3::operator!=(const Vector3& rhs) const
{
	return !(*this == rhs);
}

const Vector3 Vector3::operator-() const
{
	return Vector3(((*this)(0U) * -1.0F), ((*this)(1U) * -1.0F), ((*this)(2U) * -1.0F));
}

const Vector3 Vector3::operator-(const Vector3& rhs) const
{
	return Vector3(((*this)(0U) - rhs(0U)), ((*this)(1U) - rhs(1U)), ((*this)(2U) - rhs(2U)));
}

const Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return Vector3(((*this)(0U) + rhs(0U)), ((*this)(1U) + rhs(1U)), ((*this)(2U) + rhs(2U)));
}

const Vector3 Vector3::operator*(const Vector3& rhs) const
{
	return Vector3(((*this)(0U) * rhs(0U)), ((*this)(1U) * rhs(1U)), ((*this)(2U) * rhs(2U)));
}

const Vector3 Vector3::operator/(const Vector3& rhs) const
{
	return Vector3(((*this)(0U) / rhs(0U)), ((*this)(1U) / rhs(1U)), ((*this)(2U) / rhs(2U)));
}

const Vector3& Vector3::operator-=(const Vector3& rhs)
{
	(*this)(0U) -= rhs(0U);
	(*this)(1U) -= rhs(1U);
	(*this)(2U) -= rhs(2U);
	
	return *this;
}

const Vector3& Vector3::operator+=(const Vector3& rhs)
{
	(*this)(0U) += rhs(0U);
	(*this)(1U) += rhs(1U);
	(*this)(2U) += rhs(2U);
	
	return *this;
}

const Vector3& Vector3::operator*=(const Vector3& rhs)
{
	(*this)(0U) *= rhs(0U);
	(*this)(1U) *= rhs(1U);
	(*this)(2U) *= rhs(2U);
	
	return *this;
}

const Vector3& Vector3::operator/=(const Vector3& rhs)
{
	(*this)(0U) /= rhs(0U);
	(*this)(1U) /= rhs(1U);
	(*this)(2U) /= rhs(2U);
	
	return *this;
}

const Vector3 Vector3::operator-(const float scaler) const
{
	return Vector3(((*this)(0U) - scaler), ((*this)(1U) - scaler), ((*this)(2U) - scaler));
}

const Vector3 Vector3::operator+(const float scaler) const
{
	return Vector3(((*this)(0U) + scaler), ((*this)(1U) + scaler), ((*this)(2U) + scaler));
}

const Vector3 Vector3::operator*(const float scaler) const
{
	return Vector3(((*this)(0U) * scaler), ((*this)(1U) * scaler), ((*this)(2U) * scaler));
}

const Vector3 Vector3::operator/(const float scaler) const
{
	return Vector3(((*this)(0U) / scaler), ((*this)(1U) / scaler), ((*this)(2U) / scaler));
}

const Vector3& Vector3::operator-=(const float scaler)
{
	(*this)(0U) -= scaler;
	(*this)(1U) -= scaler;
	(*this)(2U) -= scaler;
	
	return *this;
}

const Vector3& Vector3::operator+=(const float scaler)
{
	(*this)(0U) += scaler;
	(*this)(1U) += scaler;
	(*this)(2U) += scaler;
	
	return *this;
}

const Vector3& Vector3::operator*=(const float scaler)
{
	(*this)(0U) *= scaler;
	(*this)(1U) *= scaler;
	(*this)(2U) *= scaler;
	
	return *this;
}

const Vector3& Vector3::operator/=(const float scaler)
{
	(*this)(0U) /= scaler;
	(*this)(1U) /= scaler;
	(*this)(2U) /= scaler;
	
	return *this;
}

float Vector3::operator()(const unsigned int index) const
{
	return mVector[index];
}

float& Vector3::operator()(const unsigned int index)
{
	return mVector[index];
}

void Vector3::setVector(const float x, const float y, const float z)
{
	mVector[0U] = x;
	mVector[1U] = y;
	mVector[2U] = z;
}

void Vector3::setToZero()
{
	mVector[0U] = mVector[1U] = mVector[2U] = 0.0F;
}

void Vector3::setToUnitX()
{
	mVector[0U] = 1.0F;
	mVector[1U] = mVector[2U] = 0.0F;
}

void Vector3::setToUnitY()
{
	mVector[0U] = mVector[2U] = 0.0F;
	mVector[1U] = 1.0F;
}

void Vector3::setToUnitZ()
{
	mVector[0U] = mVector[1U] = 0.0F;
	mVector[2U] = 1.0F;
}

void Vector3::lerp(const Vector3& rhs, const float time)
{
	for (unsigned int index(0U); index < 3U; ++index)
		(*this)(index) = (*this)(index) + time * (rhs(index) - (*this)(index));
}

float Vector3::getLength() const
{
	float sum(0.0F);
	for (unsigned int index(0U); index < 3U; ++index)
		sum += (mVector[index] * mVector[index]);

	return std::sqrt(sum);
}

float Vector3::getSquaredLength() const
{
	float sum(0.0F);
	for (unsigned int index(0U); index < 3U; ++index)
		sum += (mVector[index] * mVector[index]);

	return sum;
}

float Vector3::dot(const Vector3& rhs) const
{
	float sum(0.0F);
	for (unsigned int index(0U); index < 3U; ++index)
		sum += ((*this)(index) * rhs(index));

	return sum;
}

const Vector3 Vector3::cross(const Vector3& rhs) const
{
	return Vector3(((*this)(1U) * rhs(2U) - (*this)(2U) * rhs(1U)),		// x
					((*this)(2U) * rhs(0U) - (*this)(0U) * rhs(2U)),		// y
					((*this)(0U) * rhs(1U) - (*this)(1U) * rhs(0U)) );	// z
}

void Vector3::normalise()
{
	const float inverseLength(1.0F / getLength());
	for (unsigned int index(0U); index < 3U; ++index)
		mVector[index] *= inverseLength;
}

