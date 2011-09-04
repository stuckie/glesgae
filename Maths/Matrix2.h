#ifndef _MATRIX2_H_
#define _MATRIX2_H_

#include "Vector2.h"

namespace GLESGAE
{
	class Matrix2
	{
		public:
			Matrix2();

			/// Retrieve a pointer to the matrix
			float* getData() { return mMatrix; }
			
			/// Grab a const value via Matrix2(row, column);
			float operator()(const unsigned int row, const unsigned int column) const;
			
			/// Grab a reference to a value via Matrix2(row, column);
			float& operator()(const unsigned int row, const unsigned int column);

			/// Set a new matrix. This copies the matrix being passed in.
			void setMatrix(const float matrix[4U]);

			/// Set to Identity
			void setToIdentity();

			/// Set to Zero
			void setToZero();
						
			// Standard Mathy Functions
			bool operator==(const Matrix2& rhs) const;
			bool operator!=(const Matrix2& rhs) const;
			
			const Matrix2 operator+(const Matrix2& rhs) const;
			const Matrix2 operator-(const Matrix2& rhs) const;
			const Matrix2 operator*(const Matrix2& rhs) const;
			const Matrix2 operator*(const float scalar) const;
			const Matrix2 operator/(const float scalar) const;
			
			const Matrix2& operator+=(const Matrix2& rhs);
			const Matrix2& operator-=(const Matrix2& rhs);
			const Matrix2& operator*=(const Matrix2& rhs);
			
			const Matrix2& operator*=(const float scalar);
			const Matrix2& operator/=(const float scalar);

		private:
			float mMatrix[4U];
	};

}

#endif
