#ifndef _MATRIX3_H_
#define _MATRIX3_H_

#include "Vector3.h"

namespace GLESGAE
{
	class Matrix3
	{
		public:
			Matrix3();

			/// Retrieve a pointer to the matrix
			float* getData() { return mMatrix; }
			
			/// Grab a const value via Matrix3(row, column);
			float operator()(const unsigned int row, const unsigned int column) const;
			
			/// Grab a reference to a value via Matrix3(row, column);
			float& operator()(const unsigned int row, const unsigned int column);

			/// Set a new matrix. This copies the matrix being passed in.
			void setMatrix(const float matrix[9U]);

			/// Set to Identity
			void setToIdentity();

			/// Set to Zero
			void setToZero();
			
			/// Get the Front Vector
			Vector3 getFrontVector() const;
			
			/// Get the Up Vector
			Vector3 getUpVector() const;
			
			/// Get the Right Vector
			Vector3 getRightVector() const;
			
			/// Set the Front Vector
			void setFrontVector(const Vector3& vector);
			
			/// Set the Up Vector
			void setUpVector(const Vector3& vector);
			
			/// Set the Right Vector
			void setRightVector(const Vector3& vector);
			
			// Standard Mathy Functions
			bool operator==(const Matrix3& rhs) const;
			bool operator!=(const Matrix3& rhs) const;
			
			Matrix3 operator+(const Matrix3& rhs) const;
			Matrix3 operator-(const Matrix3& rhs) const;
			Matrix3 operator*(const Matrix3& rhs) const;
			Matrix3 operator*(const float scalar) const;
			Matrix3 operator/(const float scalar) const;
			
			const Matrix3& operator+=(const Matrix3& rhs);
			const Matrix3& operator-=(const Matrix3& rhs);
			const Matrix3& operator*=(const Matrix3& rhs);
			
			const Matrix3& operator*=(const float scalar);
			const Matrix3& operator/=(const float scalar);

		private:
			float mMatrix[9U];
	};

}

#endif
