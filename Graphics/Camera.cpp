#include "Camera.h"

#include <cmath>

#include "../Maths/Matrix3.h"

using namespace GLESGAE;

Camera::Camera(const CameraType& type)
: mType(type)
, mNearClip(0.1F)
, mFarClip(100.0F)
, m2dTop(1.0F)
, m2dBottom(0.0F)
, m2dLeft(0.0F)
, m2dRight(1.0F)
, mFov(45.0F)
, mAspectRatio(1.333F)
, mTransformMatrix()
, mViewMatrix()
, mProjectionMatrix()
{
}

void Camera::update()
{
	Matrix3 rotation;
	Vector3 eye;
	
	mTransformMatrix.decompose(&rotation, &eye);
	const Vector3 target(eye + rotation.getFrontVector());
	const Vector3 up(rotation.getUpVector());
	
	mViewMatrix = createViewMatrix(eye, target, up);
	
	switch (mType) {
		case CAMERA_2D:
			mProjectionMatrix = create2dProjectionMatrix(m2dLeft, m2dBottom, m2dRight, m2dTop, -mNearClip, mFarClip);
			break;
		case CAMERA_3D:
			mProjectionMatrix = create3dProjectionMatrix(mNearClip, mFarClip, mFov, mAspectRatio);
			break;
		default:
			break;
	};
}

void Camera::update(const Vector3& target)
{
	Matrix3 rotation;
	Vector3 eye;
	
	mTransformMatrix.decompose(&rotation, &eye);
	const Vector3 up(rotation.getUpVector());
	
	mViewMatrix = createViewMatrix(eye, target, up);
	
	switch (mType) {
		case CAMERA_2D:
			mProjectionMatrix = create2dProjectionMatrix(m2dLeft, m2dBottom, m2dRight, m2dTop, mNearClip, mFarClip);
			break;
		case CAMERA_3D:
			mProjectionMatrix = create3dProjectionMatrix(mNearClip, mFarClip, mFov, mAspectRatio);
			break;
		default:
			break;
	};
}

Matrix4 Camera::createViewMatrix(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 zaxis(target - eye);    // The "look-at" vector.
	zaxis.normalise();
	Vector3 xaxis(zaxis.cross(up));// The "right" vector.
	xaxis.normalise();
	Vector3 yaxis(xaxis.cross(zaxis));     // The "up" vector.
 
	// Create a 4x4 orientation matrix from the right, up, and at vectors
	Matrix4 orientation;
	orientation[0] = xaxis.x();	orientation[1] = yaxis.x();	orientation[2] = zaxis.x();	orientation[3] = 0;
	orientation[4] = xaxis.y();	orientation[5] = yaxis.y();	orientation[6] = zaxis.y();	orientation[7] = 0;
	orientation[8] = xaxis.z();	orientation[9] = yaxis.z();	orientation[10] = zaxis.z();	orientation[11] = 0;
	orientation[12] = 0;		orientation[13] = 0;		orientation[14] = 0;		orientation[15] = 1;
     
	// Create a 4x4 translation matrix by negating the eye position.
	Matrix4 translation;
	translation[0] = 1;		translation[1] = 0;		translation[2] = 0;		translation[3] = 0;
	translation[4] = 0;		translation[5] = 1;		translation[6] = 0;		translation[7] = 0;
	translation[8] = 0;		translation[9] = 0;		translation[10] = 1;		translation[11] = 0;
	translation[12] = -eye.x();	translation[13] = -eye.y();	translation[14] = -eye.z();	translation[15] = 1;
 
	// Combine the orientation and translation to compute the view matrix
	return ( translation * orientation );
}

Matrix4 Camera::create3dProjectionMatrix(const float nearClip, const float farClip, const float fov, const float aspectRatio)
{
	const float radians = fov / ((2.0F * 3.14F) / 180.0F);
	const float size = nearClip * tanf(radians); 
	float left = -size, right = size, bottom = -size / aspectRatio, top = size / aspectRatio;

	Matrix4 projectionMatrix;
	projectionMatrix(0, 0) = 2 * nearClip / (right - left);
	projectionMatrix(0, 1) = 0.0F;
	projectionMatrix(0, 2) = 0.0F;
	projectionMatrix(0, 3) = 0.0F;

	projectionMatrix(1, 0) = 0.0F;
	projectionMatrix(1, 1) = 2 * nearClip / (top - bottom);
	projectionMatrix(1, 2) = 0.0F;
	projectionMatrix(1, 3) = 0.0F;
 
	projectionMatrix(2, 0) = (right + left) / (right - left);
	projectionMatrix(2, 1) = (top + bottom) / (top - bottom);
	projectionMatrix(2, 2) = (farClip + nearClip) / (farClip - nearClip);
	projectionMatrix(2, 3) = -1.0F;

	projectionMatrix(3, 0) = 0.0F;
	projectionMatrix(3, 1) = 0.0F;
	projectionMatrix(3, 2) = (2 * farClip * nearClip) / (farClip - nearClip);
	projectionMatrix(3, 3) = 0.0F;

	return projectionMatrix;
}

Matrix4 Camera::create2dProjectionMatrix(const float left, const float bottom, const float right, const float top, const float nearClip, const float farClip)
{
	const float xScale = -2.0F / (right - left);
	const float yScale = 2.0F / (top - bottom);
	const float zScale = -2.0F / (farClip - nearClip);

	const float x = -(right + left) / (right - left);
	const float y = -(top + bottom) / (top - bottom);
	const float z = -(farClip + nearClip) / (farClip - nearClip);

	Matrix4 projectionMatrix;
	projectionMatrix(0, 0) = xScale;
	projectionMatrix(0, 1) = 0.0F;
	projectionMatrix(0, 2) = 0.0F;
	projectionMatrix(0, 3) = 0.0F;

	projectionMatrix(1, 0) = 0.0F;
	projectionMatrix(1, 1) = yScale;
	projectionMatrix(1, 2) = 0.0F;
	projectionMatrix(1, 3) = 0.0F;

	projectionMatrix(2, 0) = 0.0F;
	projectionMatrix(2, 1) = 0.0F;
	projectionMatrix(2, 2) = zScale;
	projectionMatrix(2, 3) = 0.0F;

	projectionMatrix(3, 0) = x;
	projectionMatrix(3, 1) = y;
	projectionMatrix(3, 2) = z;
	projectionMatrix(3, 3) = 1.0F;

	return projectionMatrix;
}
