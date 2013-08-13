#ifndef _VECTOR4_H_
#define _VECTOR4_H_

namespace GLESGAE
{
	class Vector4
	{
		public:
			/// Standard empty constructor
			Vector4();
			
			/// Construct with float values
			Vector4(const float x, const float y, const float z, const float w);

			/// Retrieve a pointer to the vector
			float* getData() { return mVector; }
			
			/// Equals operator
			bool operator==(const Vector4& rhs) const;
			
			/// Not Equals operator
			bool operator!=(const Vector4& rhs) const;
			
			/// Negate operator
			Vector4 operator-() const;
			
			// Standard Mathy Functions
			Vector4 operator-(const Vector4& rhs) const;
			Vector4 operator+(const Vector4& rhs) const;
			Vector4 operator*(const Vector4& rhs) const;
			Vector4 operator/(const Vector4& rhs) const;
			const Vector4& operator-=(const Vector4& rhs);
			const Vector4& operator+=(const Vector4& rhs);
			const Vector4& operator*=(const Vector4& rhs);
			const Vector4& operator/=(const Vector4& rhs);
			
			Vector4 operator-(const float scaler) const;
			Vector4 operator+(const float scaler) const;
			Vector4 operator*(const float scaler) const;
			Vector4 operator/(const float scaler) const;
			const Vector4& operator-=(const float scaler);
			const Vector4& operator+=(const float scaler);
			const Vector4& operator*=(const float scaler);
			const Vector4& operator/=(const float scaler);
			
			/// Grab a const value via Vector4(index);
			float operator()(const unsigned int index) const;
			
			/// Grab a reference to a value via Vector4(index);
			float& operator()(const unsigned int index);
			
			/// Access X
			float& x() { return mVector[0U]; } 
			float x() const { return mVector[0U]; }
			
			/// Access Y
			float& y() { return mVector[1U]; }
			float y() const { return mVector[1U]; }
			
			/// Access Z
			float& z() { return mVector[2U]; }
			float z() const { return mVector[2U]; }
			
			/// Access W
			float& w() { return mVector[3U]; }
			float w() const { return mVector[3U]; }

			/// Set the vector's x, y, z, w
			void setVector(const float x, const float y, const float z, const float w);

			/// Set to Unit X
			void setToUnitX();
			
			/// Set to Unit Y
			void setToUnitY();
			
			/// Set to Unit Z
			void setToUnitZ();

			/// Set to Unit W
			void setToUnitW();

			/// Set to Zero
			void setToZero();
			
			/// Linearly interpolate with another vector over time.
			void lerp(const Vector4& rhs, const float time);

			/// Get the length of this vector
			float getLength() const;
			
			/// Get the squared length of this vector
			float getSquaredLength() const;

			/// Get the dot product between this vector and another vector
			float dot(const Vector4& rhs) const;
			
			/// Normalise this vector
			void normalise();

		private:
			float mVector[4U];
	};

}

#endif
