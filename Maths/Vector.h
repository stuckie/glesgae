#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "../GAE_Types.h"

GAE_BOOL GAE_Vector2_compare(void* const a, void* const b);
GAE_BOOL GAE_Vector3_compare(void* const a, void* const b);
GAE_BOOL GAE_Vector4_compare(void* const a, void* const b);

GAE_Vector4_t* GAE_Vector4_add(GAE_Vector4_t* a, GAE_Vector4_t* const b);
GAE_Vector4_t* GAE_Vector4_sub(GAE_Vector4_t* a, GAE_Vector4_t* const b);
GAE_Vector4_t* GAE_Vector4_mul(GAE_Vector4_t* a, GAE_Vector4_t* const b);
GAE_Vector4_t* GAE_Vector4_div(GAE_Vector4_t* a, GAE_Vector4_t* const b);

GAE_Vector4_t* GAE_Vector4_setToZero(GAE_Vector4_t* a);
GAE_Vector4_t* GAE_Vector4_setToUnitW(GAE_Vector4_t* a);
GAE_Vector4_t* GAE_Vector4_setToUnitZ(GAE_Vector4_t* a);
GAE_Vector4_t* GAE_Vector4_setToUnitY(GAE_Vector4_t* a);
GAE_Vector4_t* GAE_Vector4_setToUnitX(GAE_Vector4_t* a);

GAE_Vector4_t* GAE_Vector4_normalise(GAE_Vector4_t* a);
GAE_Vector4_t* GAE_Vector4_lerp(GAE_Vector4_t* a, GAE_Vector4_t* const b, const GAE_Vector_t time);
GAE_Vector_t GAE_Vector4_dot(GAE_Vector4_t* const a, GAE_Vector4_t* const b);
GAE_Vector_t GAE_Vector4_squaredLength(GAE_Vector4_t* const a);
GAE_Vector_t GAE_Vector4_length(GAE_Vector4_t* const a);

GAE_Vector3_t* GAE_Vector3_add(GAE_Vector3_t* a, GAE_Vector3_t* const b);
GAE_Vector3_t* GAE_Vector3_sub(GAE_Vector3_t* a, GAE_Vector3_t* const b);
GAE_Vector3_t* GAE_Vector3_mul(GAE_Vector3_t* a, GAE_Vector3_t* const b);
GAE_Vector3_t* GAE_Vector3_div(GAE_Vector3_t* a, GAE_Vector3_t* const b);

GAE_Vector3_t* GAE_Vector3_setToZero(GAE_Vector3_t* a);
GAE_Vector3_t* GAE_Vector3_setToUnitZ(GAE_Vector3_t* a);
GAE_Vector3_t* GAE_Vector3_setToUnitY(GAE_Vector3_t* a);
GAE_Vector3_t* GAE_Vector3_setToUnitX(GAE_Vector3_t* a);
GAE_Vector3_t* GAE_Vector3_copy(GAE_Vector3_t* a, GAE_Vector3_t* const b);

GAE_Vector3_t* GAE_Vector3_normalise(GAE_Vector3_t* a);
GAE_Vector3_t* GAE_Vector3_lerp(GAE_Vector3_t* a, GAE_Vector3_t* const b, const GAE_Vector_t time);
GAE_Vector3_t* GAE_Vector3_cross(GAE_Vector3_t* const a, GAE_Vector3_t* const b, GAE_Vector3_t* c);
GAE_Vector_t GAE_Vector3_dot(GAE_Vector3_t* const a, GAE_Vector3_t* const b);
GAE_Vector_t GAE_Vector3_squaredLength(GAE_Vector3_t* const a);
GAE_Vector_t GAE_Vector3_length(GAE_Vector3_t* const a);

GAE_Vector2_t* GAE_Vector2_add(GAE_Vector2_t* a, GAE_Vector2_t* const b);
GAE_Vector2_t* GAE_Vector2_sub(GAE_Vector2_t* a, GAE_Vector2_t* const b);
GAE_Vector2_t* GAE_Vector2_mul(GAE_Vector2_t* a, GAE_Vector2_t* const b);
GAE_Vector2_t* GAE_Vector2_div(GAE_Vector2_t* a, GAE_Vector2_t* const b);

GAE_Vector2_t* GAE_Vector2_normalise(GAE_Vector2_t* a);
GAE_Vector2_t* GAE_Vector2_lerp(GAE_Vector2_t* a, GAE_Vector2_t* const b, const GAE_Vector_t time);
GAE_Vector_t GAE_Vector2_dot(GAE_Vector2_t* const a, GAE_Vector2_t* const b);
GAE_Vector_t GAE_Vector2_squaredLength(GAE_Vector2_t* const a);
GAE_Vector_t GAE_Vector2_length(GAE_Vector2_t* const a);

#endif
