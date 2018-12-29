#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "../GAE_Types.h"

GAE_BOOL GAE_Matrix4_compare(void* const a, void* const b);
GAE_BOOL GAE_Matrix3_compare(void* const a, void* const b);
GAE_BOOL GAE_Matrix2_compare(void* const a, void* const b);

GAE_Matrix2_t* GAE_Matrix2_copy(GAE_Matrix2_t* a, GAE_Matrix2_t* const b);
GAE_Matrix3_t* GAE_Matrix3_copy(GAE_Matrix3_t* a, GAE_Matrix3_t* const b);
GAE_Matrix4_t* GAE_Matrix4_copy(GAE_Matrix4_t* a, GAE_Matrix4_t* const b);

GAE_Matrix4_t* GAE_Matrix4_setToIdentity(GAE_Matrix4_t* matrix);
GAE_Matrix4_t* GAE_Matrix4_setToZero(GAE_Matrix4_t* matrix);
GAE_Matrix4_t* GAE_Matrix4_transpose(GAE_Matrix4_t* matrix);
GAE_Matrix4_t* GAE_Matrix4_decompose(GAE_Matrix4_t* const matrix, GAE_Matrix3_t* rotation, GAE_Vector3_t* position);
GAE_Matrix4_t* GAE_Matrix4_compose(GAE_Matrix4_t* matrix, GAE_Matrix3_t* const rotation, GAE_Vector3_t* const position);
GAE_Matrix4_t* GAE_Matrix4_setPosition(GAE_Matrix4_t* matrix, GAE_Vector3_t* const position);
GAE_Matrix4_t* GAE_Matrix4_setRotation(GAE_Matrix4_t* matrix, GAE_Matrix3_t* const rotation);
GAE_Matrix4_t* GAE_Matrix4_getPosition(GAE_Matrix4_t* const matrix, GAE_Vector3_t* position);
GAE_Matrix4_t* GAE_Matrix4_getRotation(GAE_Matrix4_t* const matrix, GAE_Matrix3_t* rotation);
GAE_Matrix4_t* GAE_Matrix4_setScale(GAE_Matrix4_t* matrix, GAE_Vector3_t* const scale);

GAE_Matrix4_t* GAE_Matrix4_add(GAE_Matrix4_t* matrix, GAE_Matrix4_t* const rhs);
GAE_Matrix4_t* GAE_Matrix4_sub(GAE_Matrix4_t* matrix, GAE_Matrix4_t* const rhs);
GAE_Matrix4_t* GAE_Matrix4_mul(GAE_Matrix4_t* matrix, GAE_Matrix4_t* const rhs);
GAE_Matrix4_t* GAE_Matrix4_mulVec(GAE_Matrix4_t* matrix, const GAE_Vector_t rhs);
GAE_Matrix4_t* GAE_Matrix4_div(GAE_Matrix4_t* matrix, const GAE_Vector_t rhs);

GAE_Matrix3_t* GAE_Matrix3_getFrontVector(GAE_Matrix3_t* const matrix, GAE_Vector3_t* vector);
GAE_Matrix3_t* GAE_Matrix3_getRightVector(GAE_Matrix3_t* const matrix, GAE_Vector3_t* vector);
GAE_Matrix3_t* GAE_Matrix3_getUpVector(GAE_Matrix3_t* const matrix, GAE_Vector3_t* vector);
GAE_Matrix3_t* GAE_Matrix3_setFrontVector(GAE_Matrix3_t* matrix, GAE_Vector3_t* const vector);
GAE_Matrix3_t* GAE_Matrix3_setRightVector(GAE_Matrix3_t* matrix, GAE_Vector3_t* const vector);
GAE_Matrix3_t* GAE_Matrix3_setUpVector(GAE_Matrix3_t* matrix, GAE_Vector3_t* const vector);
GAE_Matrix3_t* GAE_Matrix3_setToIdentity(GAE_Matrix3_t* matrix);
GAE_Matrix3_t* GAE_Matrix3_setToZero(GAE_Matrix3_t* matrix);

GAE_Matrix3_t* GAE_Matrix3_createXRotation(GAE_Matrix3_t* matrix, const float deg);
GAE_Matrix3_t* GAE_Matrix3_createYRotation(GAE_Matrix3_t* matrix, const float deg);
GAE_Matrix3_t* GAE_Matrix3_createZRotation(GAE_Matrix3_t* matrix, const float deg);

GAE_Matrix3_t* GAE_Matrix3_add(GAE_Matrix3_t* matrix, GAE_Matrix3_t* const rhs);
GAE_Matrix3_t* GAE_Matrix3_sub(GAE_Matrix3_t* matrix, GAE_Matrix3_t* const rhs);
GAE_Matrix3_t* GAE_Matrix3_mul(GAE_Matrix3_t* matrix, GAE_Matrix3_t* const rhs);
GAE_Matrix3_t* GAE_Matrix3_mulVec(GAE_Matrix3_t* matrix, const GAE_Vector_t rhs);
GAE_Matrix3_t* GAE_Matrix3_div(GAE_Matrix3_t* matrix, const GAE_Vector_t rhs);

GAE_Matrix2_t* GAE_Matrix2_setToIdentity(GAE_Matrix2_t* matrix);
GAE_Matrix2_t* GAE_Matrix2_setToZero(GAE_Matrix2_t* matrix);

GAE_Matrix2_t* GAE_Matrix2_add(GAE_Matrix2_t* matrix, GAE_Matrix2_t* const rhs);
GAE_Matrix2_t* GAE_Matrix2_sub(GAE_Matrix2_t* matrix, GAE_Matrix2_t* const rhs);
GAE_Matrix2_t* GAE_Matrix2_mul(GAE_Matrix2_t* matrix, GAE_Matrix2_t* const rhs);
GAE_Matrix2_t* GAE_Matrix2_mulVec(GAE_Matrix2_t* matrix, const GAE_Vector_t rhs);
GAE_Matrix2_t* GAE_Matrix2_div(GAE_Matrix2_t* matrix, const GAE_Vector_t rhs);

#endif
