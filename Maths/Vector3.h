#ifndef _VECTOR3_H_
#define _VECTOR3_H_

namespace GLESGAE
{
	class Vector3
	{
		public:
			/// Standard empty constructor
			Vector3();
			
			/// Construct with float values
			Vector3(const float x, const float y, const float z);

			/// Retrieve a pointer to the vector
			float* getData() { return mVector; }
			
			/// Equals operator
			bool operator==(const Vector3& rhs) const;
			
			/// Not Equals operator
			bool operator!=(const Vector3& rhs) const;
			
			/// Negate operator
			Vector3 operator-() const;
			
			// Standard Mathy Functions
			Vector3 operator-(const Vector3& rhs) const;
			Vector3 operator+(const Vector3& rhs) const;
			Vector3 operator*(const Vector3& rhs) const;
			Vector3 operator/(const Vector3& rhs) const;
			const Vector3& operator-=(const Vector3& rhs);
			const Vector3& operator+=(const Vector3& rhs);
			const Vector3& operator*=(const Vector3& rhs);
			const Vector3& operator/=(const Vector3& rhs);
			
			Vector3 operator-(const float scaler) const;
			Vector3 operator+(const float scaler) const;
			Vector3 operator*(const float scaler) const;
			Vector3 operator/(const float scaler) const;
			const Vector3& operator-=(const float scaler);
			const Vector3& operator+=(const float scaler);
			const Vector3& operator*=(const float scaler);
			const Vector3& operator/=(const float scaler);
			
			/// Grab a const value via Vector3(indes);
			float operator()(const unsigned int index) const;
			
			/// Grab a reference to a value via Vector3(index);
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

			/// Set the vector's x, y, z
			void setVector(const float x, const float y, const float z);

			/// Set to Unit X
			void setToUnitX();
			
			/// Set to Unit Y
			void setToUnitY();
			
			/// Set to Unit Z
			void setToUnitZ();

			/// Set to Zero
			void setToZero();
			
			/// Linearly interpolate with another vector over time.
			void lerp(const Vector3& rhs, const float time);

			/// Get the length of this vector
			float getLength() const;
			
			/// Get the squared length of this vector
			float getSquaredLength() const;

			/// Get the dot product between this vector and another vector
			float dot(const Vector3& rhs) const;
			
			/// Get the cross product between this vector and another vector
			Vector3 cross(const Vector3& rhs) const;
			
			/// Normalise this vector
			void normalise();

		private:
			float mVector[3U];
	};

}

#endif
