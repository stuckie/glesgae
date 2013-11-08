#include "Vector.h"

#include <math.h>

GAE_BOOL GAE_Vector2_compare(void* const a, void* const b) {
	GAE_Vector2_t* A = (GAE_Vector2_t*)a;
	GAE_Vector2_t* B = (GAE_Vector2_t*)b;

	return (((*A)[0]==(*B)[0]) && ((*A)[1]==(*B)[1]));
}

GAE_BOOL GAE_Vector3_compare(void* const a, void* const b) {
	GAE_Vector3_t* A = (GAE_Vector3_t*)a;
	GAE_Vector3_t* B = (GAE_Vector3_t*)b;

	return (((*A)[0]==(*B)[0]) && ((*A)[1]==(*B)[1]) && ((*A)[2]==(*B)[2]));
}

GAE_BOOL GAE_Vector4_compare(void* const a, void* const b) {
	GAE_Vector4_t* A = (GAE_Vector4_t*)a;
	GAE_Vector4_t* B = (GAE_Vector4_t*)b;

	return (((*A)[0]==(*B)[0]) && ((*A)[1]==(*B)[1]) && ((*A)[2]==(*B)[2]) && ((*A)[3]==(*B)[3]));
}

GAE_Vector4_t* GAE_Vector4_add(GAE_Vector4_t* a, GAE_Vector4_t* const b) {
	(*a)[0] += (*b)[0];
	(*a)[1] += (*b)[1];
	(*a)[2] += (*b)[2];
	(*a)[3] += (*b)[3];

	return a;
}

GAE_Vector4_t* GAE_Vector4_sub(GAE_Vector4_t* a, GAE_Vector4_t* const b) {
	(*a)[0] -= (*b)[0];
	(*a)[1] -= (*b)[1];
	(*a)[2] -= (*b)[2];
	(*a)[3] -= (*b)[3];

	return a;
}

GAE_Vector4_t* GAE_Vector4_mul(GAE_Vector4_t* a, GAE_Vector4_t* const b) {
	(*a)[0] *= (*b)[0];
	(*a)[1] *= (*b)[1];
	(*a)[2] *= (*b)[2];
	(*a)[3] *= (*b)[3];

	return a;
}

GAE_Vector4_t* GAE_Vector4_div(GAE_Vector4_t* a, GAE_Vector4_t* const b) {
	(*a)[0] /= (*b)[0];
	(*a)[1] /= (*b)[1];
	(*a)[2] /= (*b)[2];
	(*a)[3] /= (*b)[3];

	return a;
}

GAE_Vector4_t* GAE_Vector4_setToZero(GAE_Vector4_t* a) {
	(*a)[0] = (*a)[1] = (*a)[2] = (*a)[3] = 0.0F;

	return a;
}

GAE_Vector4_t* GAE_Vector4_setToUnitW(GAE_Vector4_t* a) {
	GAE_Vector4_setToZero(a);
	(*a)[3] = 1.0F;

	return a;
}

GAE_Vector4_t* GAE_Vector4_setToUnitZ(GAE_Vector4_t* a) {
	GAE_Vector4_setToZero(a);
	(*a)[2] = 1.0F;

	return a;
}

GAE_Vector4_t* GAE_Vector4_setToUnitY(GAE_Vector4_t* a) {
	GAE_Vector4_setToZero(a);
	(*a)[1] = 1.0F;

	return a;
}

GAE_Vector4_t* GAE_Vector4_setToUnitX(GAE_Vector4_t* a) {
	GAE_Vector4_setToZero(a);
	(*a)[0] = 1.0F;

	return a;
}

GAE_Vector4_t* GAE_Vector4_normalise(GAE_Vector4_t* a) {
	const float inverseLength = 1.0F / GAE_Vector4_length(a);
	unsigned int index = 0U;

	for (index = 0U; index < 4U; ++index)
		(*a)[index] *= inverseLength;

	return a;
}

GAE_Vector4_t* GAE_Vector4_lerp(GAE_Vector4_t* a, GAE_Vector4_t* const b, const GAE_Vector_t time) {
	unsigned int index = 0U;

	for (index = 0U; index < 4U; ++index)
		(*a)[index] = (*a)[index] + (time * ((*b)[index] - (*a)[index]));

	return a;
}

GAE_Vector_t GAE_Vector4_dot(GAE_Vector4_t* const a, GAE_Vector4_t* const b) {
	unsigned int index = 0U;
	float sum = 0.0F;

	for (index = 0U; index < 4U; ++index)
		sum += ((*a)[index] * (*b)[index]);

	return sum;
}

GAE_Vector_t GAE_Vector4_squaredLength(GAE_Vector4_t* const a) {
	unsigned int index = 0U;
	float sum = 0.0F;

	for (index = 0U; index < 4U; ++index)
		sum += ((*a)[index] * (*a)[index]);

	return sum;
}

GAE_Vector_t GAE_Vector4_length(GAE_Vector4_t* const a) {
	return (GAE_Vector_t)sqrt(GAE_Vector4_squaredLength(a));
}

GAE_Vector3_t* GAE_Vector3_add(GAE_Vector3_t* a, GAE_Vector3_t* const b) {
	(*a)[0] += (*b)[0];
	(*a)[1] += (*b)[1];
	(*a)[2] += (*b)[2];

	return a;
}

GAE_Vector3_t* GAE_Vector3_sub(GAE_Vector3_t* a, GAE_Vector3_t* const b) {
	(*a)[0] -= (*b)[0];
	(*a)[1] -= (*b)[1];
	(*a)[2] -= (*b)[2];

	return a;
}

GAE_Vector3_t* GAE_Vector3_mul(GAE_Vector3_t* a, GAE_Vector3_t* const b) {
	(*a)[0] *= (*b)[0];
	(*a)[1] *= (*b)[1];
	(*a)[2] *= (*b)[2];

	return a;
}

GAE_Vector3_t* GAE_Vector3_div(GAE_Vector3_t* a, GAE_Vector3_t* const b) {
	(*a)[0] /= (*b)[0];
	(*a)[1] /= (*b)[1];
	(*a)[2] /= (*b)[2];

	return a;
}

GAE_Vector3_t* GAE_Vector3_setToZero(GAE_Vector3_t* a) {
	(*a)[0] = (*a)[1] = (*a)[2] = 0.0F;

	return a;
}

GAE_Vector3_t* GAE_Vector3_setToUnitZ(GAE_Vector3_t* a) {
	GAE_Vector3_setToZero(a);
	(*a)[2] = 1.0F;

	return a;
}

GAE_Vector3_t* GAE_Vector3_setToUnitY(GAE_Vector3_t* a) {
	GAE_Vector3_setToZero(a);
	(*a)[1] = 1.0F;

	return a;
}

GAE_Vector3_t* GAE_Vector3_setToUnitX(GAE_Vector3_t* a) {
	GAE_Vector3_setToZero(a);
	(*a)[0] = 1.0F;

	return a;
}

GAE_Vector3_t* GAE_Vector3_normalise(GAE_Vector3_t* a) {
	unsigned int index = 0U;
	const float inverseLength = 1.0F / GAE_Vector3_length(a);

	for (index = 0U; index < 3U; ++index)
		(*a)[index] *= inverseLength;

	return a;
}

GAE_Vector3_t* GAE_Vector3_lerp(GAE_Vector3_t* a, GAE_Vector3_t* const b, const GAE_Vector_t time) {
	unsigned int index = 0U;
	for (index = 0U; index < 3U; ++index)
		(*a)[index] = (*a)[index] + (time * ((*b)[index] - (*a)[index]));

	return a;
}

GAE_Vector3_t* GAE_Vector3_cross(GAE_Vector3_t* const a, GAE_Vector3_t* const b, GAE_Vector3_t* c) {
	(*c)[0] = ((*a)[1] * (*b)[2]) - ((*a)[2] * (*b)[1]);
	(*c)[1] = ((*a)[2] * (*b)[0]) - ((*a)[0] * (*b)[2]);
	(*c)[2] = ((*a)[0] * (*b)[1]) - ((*a)[1] * (*b)[1]);

	return a;
}

GAE_Vector_t GAE_Vector3_dot(GAE_Vector3_t* const a, GAE_Vector3_t* const b) {
	float sum = 0.0F;
	unsigned int index = 0U;

	for (index = 0U; index < 3U; ++index)
		sum += (*a)[index] * (*b)[index];

	return sum;
}

GAE_Vector_t GAE_Vector3_squaredLength(GAE_Vector3_t* const a) {
	unsigned int index = 0U;
	GAE_Vector_t sum = 0.0F;

	for (index = 0U; index < 3U; ++index)
		sum += ((*a)[index] * (*a)[index]);

	return sum;
}

GAE_Vector_t GAE_Vector3_length(GAE_Vector3_t* const a) {
	return (GAE_Vector_t)sqrt(GAE_Vector3_squaredLength(a));
}

GAE_Vector3_t* GAE_Vector3_copy(GAE_Vector3_t* a, GAE_Vector3_t* const b) {
	(*a)[0] = (*b)[0];
	(*a)[1] = (*b)[1];
	(*a)[2] = (*b)[2];

	return a;
}

GAE_Vector2_t* GAE_Vector2_add(GAE_Vector2_t* a, GAE_Vector2_t* const b) {
	(*a)[0] += (*b)[0];
	(*a)[1] += (*b)[1];

	return a;
}

GAE_Vector2_t* GAE_Vector2_sub(GAE_Vector2_t* a, GAE_Vector2_t* const b) {
	(*a)[0] -= (*b)[0];
	(*a)[1] -= (*b)[1];

	return a;
}

GAE_Vector2_t* GAE_Vector2_mul(GAE_Vector2_t* a, GAE_Vector2_t* const b) {
	(*a)[0] *= (*b)[0];
	(*a)[1] *= (*b)[1];

	return a;
}

GAE_Vector2_t* GAE_Vector2_div(GAE_Vector2_t* a, GAE_Vector2_t* const b) {
	(*a)[0] /= (*b)[0];
	(*a)[1] /= (*b)[1];

	return a;
}

GAE_Vector2_t* GAE_Vector2_lerp(GAE_Vector2_t* a, GAE_Vector2_t* const b, const GAE_Vector_t time) {
	unsigned int index = 0U;

	for (index = 0U; index < 2U; ++index)
		(*a)[index] = (*a)[index] + (time * ((*b)[index] - (*a)[index]));

	return a;
}

GAE_Vector_t GAE_Vector2_dot(GAE_Vector2_t* const a, GAE_Vector2_t* const b) {
	unsigned int index = 0U;
	float sum = 0.0F;

	for (index = 0U; index < 2U; ++index)
		sum += (*a)[index] * (*b)[index];

	return sum;
}

GAE_Vector_t GAE_Vector2_squaredLength(GAE_Vector2_t* const a) {
	unsigned int index = 0U;
	float sum = 0.0F;

	for (index = 0U; index < 2U; ++index)
		sum += (*a)[index] * (*a)[index];

	return sum;
}

GAE_Vector_t GAE_Vector2_length(GAE_Vector2_t* const a) {
	return (GAE_Vector_t)sqrt(GAE_Vector2_squaredLength(a));
}

GAE_Vector2_t* GAE_Vector2_normalise(GAE_Vector2_t* a) {
	unsigned int index = 0U;
	const float inverseLength = 1.0F / GAE_Vector2_length(a);
	for (index = 0U; index < 2U; ++index)
		(*a)[index] *= inverseLength;

	return a;
}

