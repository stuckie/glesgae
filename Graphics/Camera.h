#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../GAE_Types.h"

typedef enum GAE_Camera_Type_e {
	GAE_CAMERA_TYPE_2D
,	GAE_CAMERA_TYPE_3D
} GAE_Camera_Type;
		
typedef struct GAE_Camera_s {
	GAE_Camera_Type type;
	
	float nearClip;
	float farClip;
	float top;
	float bottom;
	float left;
	float right;
	float fov;
	float aspect;

	GAE_Matrix4_t transform;
	GAE_Matrix4_t view;
	GAE_Matrix4_t projection;
} GAE_Camera_t;

GAE_Camera_t* GAE_Camera_create(const GAE_Camera_Type type);
GAE_Camera_t* GAE_Camera_update(GAE_Camera_t* camera);
GAE_Camera_t* GAE_Camera_lookAt(GAE_Camera_t* camera, GAE_Vector3_t* const target);
void GAE_Camera_delete(GAE_Camera_t* camera);

GAE_Matrix4_t* GAE_Matrix4_createViewMatrix(GAE_Matrix4_t* matrix, GAE_Vector3_t* const eye, GAE_Vector3_t* const centre, GAE_Vector3_t* const up);
GAE_Matrix4_t* GAE_Matrix4_create2dProjectionMatrix(GAE_Matrix4_t* matrix, const float left, const float bottom, const float right, const float top, const float nearClip, const float farClip);
GAE_Matrix4_t* GAE_Matrix4_create3dProjectionMatrix(GAE_Matrix4_t* matrix, const float nearClip, const float farClip, const float fov, const float aspect);

#endif

