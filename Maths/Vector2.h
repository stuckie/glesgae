#ifndef _VECTOR2_H_
#define _VECTOR2_H_

namespace GLESGAE
{
	class Vector2
	{
		public:
			/// Standard empty constructor
			Vector2();
			
			/// Construct with float values
			Vector2(const float x, const float y);

			/// Retrieve a pointer to the vector
			float* getData() { return mVector; }
			
			/// Equals operator
			bool operator==(const Vector2& rhs) const;
			
			/// Not Equals operator
			bool operator!=(const Vector2& rhs) const;
			
			/// Negate operator
			Vector2 operator-() const;
			
			// Standard Mathy Functions
			Vector2 operator-(const Vector2& rhs) const;
			Vector2 operator+(const Vector2& rhs) const;
			Vector2 operator*(const Vector2& rhs) const;
			Vector2 operator/(const Vector2& rhs) const;
			const Vector2& operator-=(const Vector2& rhs);
			const Vector2& operator+=(const Vector2& rhs);
			const Vector2& operator*=(const Vector2& rhs);
			const Vector2& operator/=(const Vector2& rhs);
			
			Vector2 operator-(const float scaler) const;
			Vector2 operator+(const float scaler) const;
			Vector2 operator*(const float scaler) const;
			Vector2 operator/(const float scaler) const;
			const Vector2& operator-=(const float scaler);
			const Vector2& operator+=(const float scaler);
			const Vector2& operator*=(const float scaler);
			const Vector2& operator/=(const float scaler);
			
			/// Grab a const value via Vector2(index);
			float operator()(const unsigned int index) const;
			
			/// Grab a reference to a value via Vector2(index);
			float& operator()(const unsigned int index);
			
			/// Access X
			float& x() { return mVector[0U]; } 
			float x() const { return mVector[0U]; }
			
			/// Access Y
			float& y() { return mVector[1U]; }
			float y() const { return mVector[1U]; }

			/// Set the vector's x, y
			void setVector(const float x, const float y);

			/// Set to Unit X
			void setToUnitX();
			
			/// Set to Unit Y
			void setToUnitY();

			/// Set to Zero
			void setToZero();
			
			/// Linearly interpolate with another vector over time.
			void lerp(const Vector2& rhs, const float time);

			/// Get the length of this vector
			float getLength() const;
			
			/// Get the squared length of this vector
			float getSquaredLength() const;

			/// Get the dot product between this vector and another vector
			float dot(const Vector2& rhs) const;
			
			/// Normalise this vector
			void normalise();

		private:
			float mVector[2U];
	};

}

#endif

