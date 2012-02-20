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

Matrix4 Camera::createViewMatrix(const Vector3& eye, const Vector3& centre, const Vector3& up)
{
	Vector3 forwardVector(centre - eye);
	forwardVector.normalise();

	Vector3 rightVector(forwardVector.cross(up));
	rightVector.normalise();

	// We recompute the Up vector to make sure that everything is exactly perpendicular to one another.
 	// Otherwise, there can be rounding errors and things go a bit mad!
	// We can also do this to assert and check that our up vector actually matches up properly.
	Vector3 upVector(rightVector.cross(forwardVector));

	Matrix4 viewMatrix;
	viewMatrix(0, 0) = -rightVector.x();
	viewMatrix(0, 1) = upVector.x();
	viewMatrix(0, 2) = forwardVector.x();
	viewMatrix(0, 3) = 0.0F;
	
	viewMatrix(1, 0) = -rightVector.y();
	viewMatrix(1, 1) = upVector.y();
	viewMatrix(1, 2) = forwardVector.y();
	viewMatrix(1, 3) = 0.0F;
	
	viewMatrix(2, 0) = -rightVector.z();
	viewMatrix(2, 1) = upVector.z();
	viewMatrix(2, 2) = forwardVector.z();
	viewMatrix(2, 3) = 0.0F;
	
	viewMatrix(3, 0) = 0.0F;
	viewMatrix(3, 1) = 0.0F;
	viewMatrix(3, 2) = 0.0F;
	viewMatrix(3, 3) = 1.0F;

	// We then need to translate our eye back to the origin, and use this as effectively the View's position.
	// An eye does have a position in space, after all! As does a Window.
	viewMatrix(3, 0) = (viewMatrix(0, 0) * -eye.x() + viewMatrix(1, 0) * -eye.y() + viewMatrix(2, 0) * -eye.z());
	viewMatrix(3, 1) = (viewMatrix(0, 1) * -eye.x() + viewMatrix(1, 1) * -eye.y() + viewMatrix(2, 1) * -eye.z());
	viewMatrix(3, 2) = (viewMatrix(0, 2) * -eye.x() + viewMatrix(1, 2) * -eye.y() + viewMatrix(2, 2) * -eye.z());

	return viewMatrix;
}

Matrix4 Camera::create3dProjectionMatrix(const float nearClip, const float farClip, const float fov, const float aspectRatio)
{
 	const float radians = fov / 2.0F * 3.14F / 180.0F;
	const float zDelta = farClip - nearClip;
	const float sine = sin(radians);
	const float cotangent = cos(radians) / sine;

	Matrix4 projectionMatrix;
	projectionMatrix(0, 0) = cotangent / aspectRatio;
	projectionMatrix(0, 1) = 0.0F;
	projectionMatrix(0, 2) = 0.0F;
	projectionMatrix(0, 3) = 0.0F;

	projectionMatrix(1, 0) = 0.0F;
	projectionMatrix(1, 1) = cotangent;
	projectionMatrix(1, 2) = 0.0F;
	projectionMatrix(1, 3) = 0.0F;
 
	projectionMatrix(2, 0) = 0.0F;
	projectionMatrix(2, 1) = 0.0F;
	projectionMatrix(2, 2) = -(farClip + nearClip) / zDelta;
	projectionMatrix(2, 3) = -1.0F;

	projectionMatrix(3, 0) = 0.0F;
	projectionMatrix(3, 1) = 0.0F;
	projectionMatrix(3, 2) = -2.0F * nearClip * farClip / zDelta;
	projectionMatrix(3, 3) = 0.0F;

	return projectionMatrix;
}

Matrix4 Camera::create2dProjectionMatrix(const float left, const float bottom, const float right, const float top, const float nearClip, const float farClip)
{
	const float xScale = 2.0F / (right - left);
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

