#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../Maths/Vector3.h"
#include "../Maths/Matrix4.h"

namespace GLESGAE
{
	class Camera
	{
		public:
			enum CameraType
			{
				CAMERA_2D
			,	CAMERA_3D
			};
		
			Camera(const CameraType& type);
		
			/// Get the Type of Camera this is
			CameraType getType() { return mType; }
		
			/// Update the camera's View and Projection matrices while looking ahead.
			void update();
			
			/// Update the camera's View and Projection matrices while looking at something.
			void update(const Vector3& target);
			
			/// Set Near Clip
			void setNearClip(const float nearClip) { mNearClip = nearClip; }
			
			/// Set Far Clip
			void setFarClip(const float farClip) { mFarClip = farClip; }
			
			/// Set 2d Parameters
			void set2dParams(const float left, const float bottom, const float right, const float top) { m2dLeft = left; m2dRight = right; m2dTop = top; m2dBottom = bottom; }
			
			/// Set 3d Parameters
			void set3dParams(const float fov, const float aspectRatio) { mFov = fov; mAspectRatio = aspectRatio; }
			
			/// Set the Transform Matrix
			void setTransformMatrix(const Matrix4& transformMatrix) { mTransformMatrix = transformMatrix; }
			
			/// Set the View Matrix
			void setViewMatrix(const Matrix4& viewMatrix) { mViewMatrix = viewMatrix; }
			
			/// Set the Projection Matrix
			void setProjectionMatrix(const Matrix4& projectionMatrix) { mProjectionMatrix = projectionMatrix; }
			
			/// Get the Transform Matrix
			Matrix4& getTransformMatrix() { return mTransformMatrix; }
			
			/// Get a Const version of the Transform Matrix
			const Matrix4& getTransformMatrix() const { return mTransformMatrix; }
			
			/// Get the View Matrix
			const Matrix4& getViewMatrix() const { return mViewMatrix; }
			
			/// Get a writable view matrix
			Matrix4& getViewMatrix() { return mViewMatrix; }
			
			/// Get the Projection Matrix
			const Matrix4& getProjectionMatrix() const { return mProjectionMatrix; }
			
			/// Get Near Clip
			float getNearClip() const { return mNearClip; }
			
			/// Get Far Clip
			float getFarClip() const { return mFarClip; }
			
			/// Get Field of View
			float getFov() const { return mFov; }
			
			/// Get Aspect Ratio
			float getAspectRatio() const { return mAspectRatio; }
			
			/// Create a viewMatrix
			static Matrix4 createViewMatrix(const Vector3& eye, const Vector3& centre, const Vector3& up);
			
			/// Create a 2d projection matrix
			static Matrix4 create2dProjectionMatrix(const float left, const float bottom, const float right, const float top, const float nearClip, const float farClip);
			
			/// Create a 3d projection matrix
			static Matrix4 create3dProjectionMatrix(const float nearClip, const float farClip, const float fov, const float aspectRatio);
			

		private:
			CameraType mType;
			
			float mNearClip;
			float mFarClip;
			float m2dTop;
			float m2dBottom;
			float m2dLeft;
			float m2dRight;
			float mFov;
			float mAspectRatio;
			
			Matrix4 mTransformMatrix;
			Matrix4 mViewMatrix;
			Matrix4 mProjectionMatrix;
	};
}

#endif

