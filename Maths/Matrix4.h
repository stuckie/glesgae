#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Matrix3.h"
#include "Vector3.h"

namespace GLESGAE
{
	class Matrix4
	{
		public:
			Matrix4();

			/// Retrieve a pointer to the matrix
			float* getData() { return mMatrix; }
			const float* getData() const { return mMatrix; }
			
			/// Grab a const value via Matrix4(row, column);
			float operator()(const unsigned int row, const unsigned int column) const;
			
			/// Grab a reference to a value via Matrix4(row, column);
			float& operator()(const unsigned int row, const unsigned int column);
			
			/// Grab a const value via Matrix[index]
			float operator[](const unsigned int index) const;
			
			/// Grab a reference value via Matrix[index]
			float& operator[](const unsigned int index);

			/// Set a new matrix. This copies the matrix being passed in.
			void setMatrix(const float matrix[16U]);

			/// Set to Identity
			void setToIdentity();

			/// Set to Zero
			void setToZero();
			
			/// Get Transposed Matrix
			Matrix4 getTranspose() const;
			
			/// Decompose matrix into rotation matrix and position vector.
			void decompose(Matrix3* rotation, Vector3* position) const;
			
			/// Compose matrix from rotation matrix and position vector.
			void compose(const Matrix3& rotation, const Vector3& position);
			
			/// Set just the position
			void setPosition(const Vector3& position);
			
			/// Set just the rotation
			void setRotation(const Matrix3& rotation);
			
			/// Get just the position
			void getPosition(Vector3* position) const;
			
			/// Get just the rotation
			void getRotation(Matrix3* rotation) const;
			
			/// Set Scale
			void setScale(const Vector3& scale);
			
			// Standard Mathy Functions
			bool operator==(const Matrix4& rhs) const;
			bool operator!=(const Matrix4& rhs) const;
			
			const Matrix4 operator+(const Matrix4& rhs) const;
			const Matrix4 operator-(const Matrix4& rhs) const;
			const Matrix4 operator*(const Matrix4& rhs) const;
			const Matrix4 operator*(const float scalar) const;
			const Matrix4 operator/(const float scalar) const;
			
			const Matrix4& operator+=(const Matrix4& rhs);
			const Matrix4& operator-=(const Matrix4& rhs);
			const Matrix4& operator*=(const Matrix4& rhs);
			
			const Matrix4& operator*=(const float scalar);
			const Matrix4& operator/=(const float scalar);

		private:
			float mMatrix[16U];
	};

}

#endif
