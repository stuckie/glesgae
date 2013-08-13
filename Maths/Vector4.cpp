#include "Vector4.h"

#include <cmath>

using namespace GLESGAE;

Vector4::Vector4()
: mVector()
{
	setToZero();
}

Vector4::Vector4(const float x, const float y, const float z, const float w)
: mVector()
{
	mVector[0U] = x;
	mVector[1U] = y;
	mVector[2U] = z;
	mVector[3U] = w;
}

bool Vector4::operator==(const Vector4& rhs) const
{
	return (((*this)(0U) == rhs(0U))
		&&	((*this)(1U) == rhs(1U))
		&&	((*this)(2U) == rhs(2U))
		&&	((*this)(3U) == rhs(3U)));
}

bool Vector4::operator!=(const Vector4& rhs) const
{
	return !(*this == rhs);
}

Vector4 Vector4::operator-() const
{
	return Vector4(((*this)(0U) * -1.0F), ((*this)(1U) * -1.0F), ((*this)(2U) * -1.0F), ((*this)(3U) * -1.0F));
}

Vector4 Vector4::operator-(const Vector4& rhs) const
{
	return Vector4(((*this)(0U) - rhs(0U)), ((*this)(1U) - rhs(1U)), ((*this)(2U) - rhs(2U)), ((*this)(3U) - rhs(3U)));
}

Vector4 Vector4::operator+(const Vector4& rhs) const
{
	return Vector4(((*this)(0U) + rhs(0U)), ((*this)(1U) + rhs(1U)), ((*this)(2U) + rhs(2U)), ((*this)(3U) + rhs(3U)));
}

Vector4 Vector4::operator*(const Vector4& rhs) const
{
	return Vector4(((*this)(0U) * rhs(0U)), ((*this)(1U) * rhs(1U)), ((*this)(2U) * rhs(2U)), ((*this)(3U) * rhs(3U)));
}

Vector4 Vector4::operator/(const Vector4& rhs) const
{
	return Vector4(((*this)(0U) / rhs(0U)), ((*this)(1U) / rhs(1U)), ((*this)(2U) / rhs(2U)), ((*this)(3U) / rhs(3U)));
}

const Vector4& Vector4::operator-=(const Vector4& rhs)
{
	(*this)(0U) -= rhs(0U);
	(*this)(1U) -= rhs(1U);
	(*this)(2U) -= rhs(2U);
	(*this)(3U) -= rhs(3U);
	
	return *this;
}

const Vector4& Vector4::operator+=(const Vector4& rhs)
{
	(*this)(0U) += rhs(0U);
	(*this)(1U) += rhs(1U);
	(*this)(2U) += rhs(2U);
	(*this)(3U) += rhs(3U);
	
	return *this;
}

const Vector4& Vector4::operator*=(const Vector4& rhs)
{
	(*this)(0U) *= rhs(0U);
	(*this)(1U) *= rhs(1U);
	(*this)(2U) *= rhs(2U);
	(*this)(3U) *= rhs(3U);
	
	return *this;
}

const Vector4& Vector4::operator/=(const Vector4& rhs)
{
	(*this)(0U) /= rhs(0U);
	(*this)(1U) /= rhs(1U);
	(*this)(2U) /= rhs(2U);
	(*this)(3U) /= rhs(3U);
	
	return *this;
}

Vector4 Vector4::operator-(const float scaler) const
{
	return Vector4(((*this)(0U) - scaler), ((*this)(1U) - scaler), ((*this)(2U) - scaler), ((*this)(3U) - scaler));
}

Vector4 Vector4::operator+(const float scaler) const
{
	return Vector4(((*this)(0U) + scaler), ((*this)(1U) + scaler), ((*this)(2U) + scaler), ((*this)(3U) + scaler));
}

Vector4 Vector4::operator*(const float scaler) const
{
	return Vector4(((*this)(0U) * scaler), ((*this)(1U) * scaler), ((*this)(2U) * scaler), ((*this)(3U) * scaler));
}

Vector4 Vector4::operator/(const float scaler) const
{
	return Vector4(((*this)(0U) / scaler), ((*this)(1U) / scaler), ((*this)(2U) / scaler), ((*this)(3U) / scaler));
}

const Vector4& Vector4::operator-=(const float scaler)
{
	(*this)(0U) -= scaler;
	(*this)(1U) -= scaler;
	(*this)(2U) -= scaler;
	(*this)(3U) -= scaler;
	
	return *this;
}

const Vector4& Vector4::operator+=(const float scaler)
{
	(*this)(0U) += scaler;
	(*this)(1U) += scaler;
	(*this)(2U) += scaler;
	(*this)(3U) += scaler;
	
	return *this;
}

const Vector4& Vector4::operator*=(const float scaler)
{
	(*this)(0U) *= scaler;
	(*this)(1U) *= scaler;
	(*this)(2U) *= scaler;
	(*this)(3U) *= scaler;
	
	return *this;
}

const Vector4& Vector4::operator/=(const float scaler)
{
	(*this)(0U) /= scaler;
	(*this)(1U) /= scaler;
	(*this)(2U) /= scaler;
	(*this)(3U) /= scaler;
	
	return *this;
}

float Vector4::operator()(const unsigned int index) const
{
	return mVector[index];
}

float& Vector4::operator()(const unsigned int index)
{
	return mVector[index];
}

void Vector4::setVector(const float x, const float y, const float z, const float w)
{
	mVector[0U] = x;
	mVector[1U] = y;
	mVector[2U] = z;
	mVector[3U] = w;
}

void Vector4::setToZero()
{
	mVector[0U] = mVector[1U] = mVector[2U] = mVector[3U] = 0.0F;
}

void Vector4::setToUnitX()
{
	mVector[0U] = 1.0F;
	mVector[1U] = mVector[2U] = mVector[3U] = 0.0F;
}

void Vector4::setToUnitY()
{
	mVector[0U] = mVector[2U] = mVector[3U] = 0.0F;
	mVector[1U] = 1.0F;
}

void Vector4::setToUnitZ()
{
	mVector[0U] = mVector[1U] = mVector[3U] = 0.0F;
	mVector[2U] = 1.0F;
}

void Vector4::setToUnitW()
{
	mVector[0U] = mVector[1U] = mVector[2U] = 0.0F;
	mVector[3U] = 1.0F;
}

void Vector4::lerp(const Vector4& rhs, const float time)
{
	for (unsigned int index(0U); index < 4U; ++index)
		(*this)(index) = (*this)(index) + time * (rhs(index) - (*this)(index));
}

float Vector4::getLength() const
{
	float sum(0.0F);
	for (unsigned int index(0U); index < 4U; ++index)
		sum += (mVector[index] * mVector[index]);

	return std::sqrt(sum);
}

float Vector4::getSquaredLength() const
{
	float sum(0.0F);
	for (unsigned int index(0U); index < 4U; ++index)
		sum += (mVector[index] * mVector[index]);

	return sum;
}

float Vector4::dot(const Vector4& rhs) const
{
	float sum(0.0F);
	for (unsigned int index(0U); index < 4U; ++index)
		sum += ((*this)(index) * rhs(index));

	return sum;
}

void Vector4::normalise()
{
	const float inverseLength(1.0F / getLength());
	for (unsigned int index(0U); index < 4U; ++index)
		mVector[index] *= inverseLength;
}

