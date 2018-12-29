#include "Camera.h"

#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "../Maths/Matrix.h"
#include "../Maths/Vector.h"

#define ROWCOL(x,y,width) (x * width + y)

GAE_Camera_t* GAE_Camera_create(const GAE_Camera_Type type) {
	GAE_Camera_t* camera = malloc(sizeof(GAE_Camera_t));

	camera->type = type;
	camera->nearClip = 0.1F;
	camera->farClip = 100.0F;
	camera->top = 1.0F;
	camera->bottom = 0.0F;
	camera->left = 0.0F;
	camera->right = 1.0F;
	camera->fov = 45.0F;
	camera->aspect = 1.333F;

	GAE_Matrix4_setToIdentity(&camera->transform);
	GAE_Matrix4_setToIdentity(&camera->view);
	GAE_Matrix4_setToIdentity(&camera->projection);

	return camera;
}

GAE_Camera_t* GAE_Camera_update(GAE_Camera_t* camera) {
	GAE_Matrix3_t rotation;
	GAE_Vector3_t eye;
	GAE_Vector3_t target;
	GAE_Vector3_t up;
	GAE_Vector3_t front;

	GAE_Matrix4_decompose(&camera->transform, &rotation, &eye);
	GAE_Vector3_copy(&target, &eye);
	GAE_Matrix3_getFrontVector(&rotation, &front);
	GAE_Vector3_add(&target, &front);
	GAE_Matrix3_getUpVector(&rotation, &up);

	GAE_Matrix4_createViewMatrix(&camera->view, &eye, &target, &up);

	switch (camera->type) {
		case GAE_CAMERA_TYPE_2D:
			GAE_Matrix4_create2dProjectionMatrix(&camera->projection, camera->left, camera->bottom, camera->right, camera->top, -camera->nearClip, camera->farClip);
			break;
		case GAE_CAMERA_TYPE_3D:
			GAE_Matrix4_create3dProjectionMatrix(&camera->projection, camera->nearClip, camera->farClip, camera->fov, camera->aspect);
			break;
		default:
		break;
	};

	return camera;
}

GAE_Camera_t* GAE_Camera_lookAt(GAE_Camera_t* camera, GAE_Vector3_t* const target) {
	GAE_Matrix3_t rotation;
	GAE_Vector3_t eye;
	GAE_Vector3_t up;
	
	GAE_Matrix4_decompose(&camera->transform, &rotation, &eye);
	GAE_Matrix3_getUpVector(&rotation, &up);
	
	GAE_Matrix4_createViewMatrix(&camera->view, &eye, target, &up);
	
	switch (camera->type) {
		case GAE_CAMERA_TYPE_2D:
			GAE_Matrix4_create2dProjectionMatrix(&camera->projection, camera->left, camera->bottom, camera->right, camera->top, -camera->nearClip, camera->farClip);
			break;
		case GAE_CAMERA_TYPE_3D:
			GAE_Matrix4_create3dProjectionMatrix(&camera->projection, camera->nearClip, camera->farClip, camera->fov, camera->aspect);
			break;
		default:
		break;
	};

	return camera;
}

void GAE_Camera_delete(GAE_Camera_t* camera) {
	free(camera);
	camera = 0;
}

GAE_Matrix4_t* GAE_Matrix4_createViewMatrix(GAE_Matrix4_t* matrix, GAE_Vector3_t* const eye, GAE_Vector3_t* const centre, GAE_Vector3_t* const up) {
	GAE_Vector3_t zaxis;
	GAE_Vector3_t xaxis;
	GAE_Vector3_t yaxis;

	GAE_Matrix4_t orientation;
	GAE_Matrix4_t translation;

	GAE_Vector3_copy(&zaxis, centre);
	GAE_Vector3_sub(&zaxis, eye);
	GAE_Vector3_normalise(&zaxis);
	
	GAE_Vector3_cross(&zaxis, up, &xaxis);
	GAE_Vector3_normalise(&xaxis);
	
	GAE_Vector3_cross(&xaxis, &zaxis, &yaxis);
	
 	/* Create a 4x4 orientation matrix from the right, up, and at vectors */
	orientation[0] = xaxis[0];	orientation[1] = yaxis[0];	orientation[2] = zaxis[0];	orientation[3] = 0;
	orientation[4] = xaxis[1];	orientation[5] = yaxis[1];	orientation[6] = zaxis[1];	orientation[7] = 0;
	orientation[8] = xaxis[2];	orientation[9] = yaxis[2];	orientation[10] = zaxis[2];	orientation[11] = 0;
	orientation[12] = 0;		orientation[13] = 0;		orientation[14] = 0;		orientation[15] = 1;
	 
	/* Create a 4x4 translation matrix by negating the eye position.*/
	translation[0] = 1;		translation[1] = 0;		translation[2] = 0;		translation[3] = 0;
	translation[4] = 0;		translation[5] = 1;		translation[6] = 0;		translation[7] = 0;
	translation[8] = 0;		translation[9] = 0;		translation[10] = 1;		translation[11] = 0;
	translation[12] = -(*eye)[0];	translation[13] = -(*eye)[1];	translation[14] = -(*eye)[2];	translation[15] = 1;
	
	/* Combine the orientation and translation to compute the view matrix*/
	GAE_Matrix4_mul(&translation, &orientation);
	GAE_Matrix4_copy(matrix, &translation);

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_create3dProjectionMatrix(GAE_Matrix4_t* projectionMatrix, const float nearClip, const float farClip, const float fov, const float aspectRatio) {
	const float radians = fov / ((2.0F * 3.14F) / 180.0F);
	const float size = nearClip * tanf(radians); 
	const float left = -size;
	const float right = size;
	const float bottom = -size / aspectRatio;
	const float top = size / aspectRatio;

	(*projectionMatrix)[ROWCOL(0, 0, 4)] = 2 * nearClip / (right - left);
	(*projectionMatrix)[ROWCOL(0, 1, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(0, 2, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(0, 3, 4)] = 0.0F;

	(*projectionMatrix)[ROWCOL(1, 0, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(1, 1, 4)] = 2 * nearClip / (top - bottom);
	(*projectionMatrix)[ROWCOL(1, 2, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(1, 3, 4)] = 0.0F;
 
	(*projectionMatrix)[ROWCOL(2, 0, 4)] = (right + left) / (right - left);
	(*projectionMatrix)[ROWCOL(2, 1, 4)] = (top + bottom) / (top - bottom);
	(*projectionMatrix)[ROWCOL(2, 2, 4)] = (farClip + nearClip) / (farClip - nearClip);
	(*projectionMatrix)[ROWCOL(2, 3, 4)] = -1.0F;

	(*projectionMatrix)[ROWCOL(3, 0, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(3, 1, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(3, 2, 4)] = (2 * farClip * nearClip) / (farClip - nearClip);
	(*projectionMatrix)[ROWCOL(3, 3, 4)] = 0.0F;

	return projectionMatrix;
}

GAE_Matrix4_t* GAE_Matrix4_create2dProjectionMatrix(GAE_Matrix4_t* projectionMatrix, const float left, const float bottom, const float right, const float top, const float nearClip, const float farClip) {
	const float xScale = -2.0F / (right - left);
	const float yScale = 2.0F / (top - bottom);
	const float zScale = -2.0F / (farClip - nearClip);

	const float x = -(right + left) / (right - left);
	const float y = -(top + bottom) / (top - bottom);
	const float z = -(farClip + nearClip) / (farClip - nearClip);

	(*projectionMatrix)[ROWCOL(0, 0, 4)] = xScale;
	(*projectionMatrix)[ROWCOL(0, 1, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(0, 2, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(0, 3, 4)] = 0.0F;

	(*projectionMatrix)[ROWCOL(1, 0, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(1, 1, 4)] = yScale;
	(*projectionMatrix)[ROWCOL(1, 2, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(1, 3, 4)] = 0.0F;

	(*projectionMatrix)[ROWCOL(2, 0, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(2, 1, 4)] = 0.0F;
	(*projectionMatrix)[ROWCOL(2, 2, 4)] = zScale;
	(*projectionMatrix)[ROWCOL(2, 3, 4)] = 0.0F;

	(*projectionMatrix)[ROWCOL(3, 0, 4)] = x;
	(*projectionMatrix)[ROWCOL(3, 1, 4)] = y;
	(*projectionMatrix)[ROWCOL(3, 2, 4)] = z;
	(*projectionMatrix)[ROWCOL(3, 3, 4)] = 1.0F;

	return projectionMatrix;
}
