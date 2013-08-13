#include "Vector2.h"

#include <cmath>

using namespace GLESGAE;

Vector2::Vector2()
: mVector()
{
	setToZero();
}

Vector2::Vector2(const float x, const float y)
: mVector()
{
	mVector[0U] = x;
	mVector[1U] = y;
}

bool Vector2::operator==(const Vector2& rhs) const
{
	return (((*this)(0U) == rhs(0U))
		&&	((*this)(1U) == rhs(1U)));
}

bool Vector2::operator!=(const Vector2& rhs) const
{
	return !(*this == rhs);
}

Vector2 Vector2::operator-() const
{
	return Vector2(((*this)(0U) * -1.0F), ((*this)(1U) * -1.0F));
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(((*this)(0U) - rhs(0U)), ((*this)(1U) - rhs(1U)));
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(((*this)(0U) + rhs(0U)), ((*this)(1U) + rhs(1U)));
}

Vector2 Vector2::operator*(const Vector2& rhs) const
{
	return Vector2(((*this)(0U) * rhs(0U)), ((*this)(1U) * rhs(1U)));
}

Vector2 Vector2::operator/(const Vector2& rhs) const
{
	return Vector2(((*this)(0U) / rhs(0U)), ((*this)(1U) / rhs(1U)));
}

const Vector2& Vector2::operator-=(const Vector2& rhs)
{
	(*this)(0U) -= rhs(0U);
	(*this)(1U) -= rhs(1U);
	
	return *this;
}

const Vector2& Vector2::operator+=(const Vector2& rhs)
{
	(*this)(0U) += rhs(0U);
	(*this)(1U) += rhs(1U);
	
	return *this;
}

const Vector2& Vector2::operator*=(const Vector2& rhs)
{
	(*this)(0U) *= rhs(0U);
	(*this)(1U) *= rhs(1U);
	
	return *this;
}

const Vector2& Vector2::operator/=(const Vector2& rhs)
{
	(*this)(0U) /= rhs(0U);
	(*this)(1U) /= rhs(1U);
	
	return *this;
}

Vector2 Vector2::operator-(const float scaler) const
{
	return Vector2(((*this)(0U) - scaler), ((*this)(1U) - scaler));
}

Vector2 Vector2::operator+(const float scaler) const
{
	return Vector2(((*this)(0U) + scaler), ((*this)(1U) + scaler));
}

Vector2 Vector2::operator*(const float scaler) const
{
	return Vector2(((*this)(0U) * scaler), ((*this)(1U) * scaler));
}

Vector2 Vector2::operator/(const float scaler) const
{
	return Vector2(((*this)(0U) / scaler), ((*this)(1U) / scaler));
}

const Vector2& Vector2::operator-=(const float scaler)
{
	(*this)(0U) -= scaler;
	(*this)(1U) -= scaler;
	
	return *this;
}

const Vector2& Vector2::operator+=(const float scaler)
{
	(*this)(0U) += scaler;
	(*this)(1U) += scaler;
	
	return *this;
}

const Vector2& Vector2::operator*=(const float scaler)
{
	(*this)(0U) *= scaler;
	(*this)(1U) *= scaler;
	
	return *this;
}

const Vector2& Vector2::operator/=(const float scaler)
{
	(*this)(0U) /= scaler;
	(*this)(1U) /= scaler;
	
	return *this;
}

float Vector2::operator()(const unsigned int index) const
{
	return mVector[index];
}

float& Vector2::operator()(const unsigned int index)
{
	return mVector[index];
}

void Vector2::setVector(const float x, const float y)
{
	mVector[0U] = x;
	mVector[1U] = y;
}

void Vector2::setToZero()
{
	mVector[0U] = mVector[1U] = 0.0F;
}

void Vector2::setToUnitX()
{
	mVector[0U] = 1.0F;
	mVector[1U] = 0.0F;
}

void Vector2::setToUnitY()
{
	mVector[0U] = 0.0F;
	mVector[1U] = 1.0F;
}

void Vector2::lerp(const Vector2& rhs, const float time)
{
	for (unsigned int index(0U); index < 2U; ++index)
		(*this)(index) = (*this)(index) + time * (rhs(index) - (*this)(index));
}

float Vector2::getLength() const
{
	float sum(0.0F);
	for (unsigned int index(0U); index < 2U; ++index)
		sum += (mVector[index] * mVector[index]);

	return std::sqrt(sum);
}

float Vector2::getSquaredLength() const
{
	float sum(0.0F);
	for (unsigned int index(0U); index < 2U; ++index)
		sum += (mVector[index] * mVector[index]);

	return sum;
}

float Vector2::dot(const Vector2& rhs) const
{
	float sum(0.0F);
	for (unsigned int index(0U); index < 2U; ++index)
		sum += ((*this)(index) * rhs(index));

	return sum;
}

void Vector2::normalise()
{
	const float inverseLength(1.0F / getLength());
	for (unsigned int index(0U); index < 2U; ++index)
		mVector[index] *= inverseLength;
}

