#include "Matrix.h"

#include <math.h>
#include <string.h>

#define ROWCOL(x,y,width) (x * width + y)

GAE_BOOL GAE_Matrix4_compare(void* const a, void* const b) {
	GAE_Matrix4_t* A = (GAE_Matrix4_t*)a;
	GAE_Matrix4_t* B = (GAE_Matrix4_t*)b;

	return (((*A)[0] == (*B)[0]) && ((*A)[1] == (*B)[1]) && ((*A)[2] == (*B)[2]) && ((*A)[3] == (*B)[3])
		&& ((*A)[4] == (*B)[4]) && ((*A)[5] == (*B)[5]) && ((*A)[6] == (*B)[6]) && ((*A)[7] == (*B)[7])
		&& ((*A)[8] == (*B)[8]) && ((*A)[9] == (*B)[9]) && ((*A)[10] == (*B)[10]) && ((*A)[11] == (*B)[11])
		&& ((*A)[12] == (*B)[12]) && ((*A)[13] == (*B)[13]) && ((*A)[14] == (*B)[14]) && ((*A)[15] == (*B)[15]));
}

GAE_BOOL GAE_Matrix3_compare(void* const a, void* const b) {
	GAE_Matrix3_t* A = (GAE_Matrix3_t*)a;
	GAE_Matrix3_t* B = (GAE_Matrix3_t*)b;

	return (((*A)[0] == (*B)[0]) && ((*A)[1] == (*B)[1]) && ((*A)[2] == (*B)[2])
		&& ((*A)[3] == (*B)[3]) && ((*A)[4] == (*B)[4]) && ((*A)[5] == (*B)[5])
		&& ((*A)[6] == (*B)[6]) && ((*A)[7] == (*B)[7]) && ((*A)[8] == (*B)[8]));
}
GAE_BOOL GAE_Matrix2_compare(void* const a, void* const b) {
	GAE_Matrix2_t* A = (GAE_Matrix2_t*)a;
	GAE_Matrix2_t* B = (GAE_Matrix2_t*)b;

	return (((*A)[0] == (*B)[0]) && ((*A)[1] == (*B)[1])
		&& ((*A)[2] == (*B)[2]) && ((*A)[3] == (*B)[3]));
}

GAE_Matrix2_t* GAE_Matrix2_copy(GAE_Matrix2_t* a, GAE_Matrix2_t* const b) {
	unsigned int index = 0U;
	for (index = 0U; index < 4U; ++index)
		(*a)[index] = (*b)[index];

	return a;
}

GAE_Matrix3_t* GAE_Matrix3_copy(GAE_Matrix3_t* a, GAE_Matrix3_t* const b) {
	unsigned int index = 0U;
	for (index = 0U; index < 9U; ++index)
		(*a)[index] = (*b)[index];
	
	return a;
}

GAE_Matrix4_t* GAE_Matrix4_copy(GAE_Matrix4_t* a, GAE_Matrix4_t* const b) {
	unsigned int index = 0U;
	for (index = 0U; index < 16U; ++index)
		(*a)[index] = (*b)[index];
	
	return a;
}

GAE_Matrix4_t* GAE_Matrix4_setToIdentity(GAE_Matrix4_t* matrix) {
	GAE_Matrix4_setToZero(matrix);
	(*matrix)[0] = (*matrix)[5] = (*matrix)[10] = (*matrix)[15] = 1.0F;

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_setToZero(GAE_Matrix4_t* matrix) {
	(*matrix)[0] = (*matrix)[1] = (*matrix)[2] = (*matrix)[3] = 0.0F; 
	(*matrix)[4] = (*matrix)[5] = (*matrix)[6] = (*matrix)[7] = 0.0F;
	(*matrix)[8] = (*matrix)[9] = (*matrix)[10] = (*matrix)[11] = 0.0F; 
	(*matrix)[12] = (*matrix)[13] = (*matrix)[14] = (*matrix)[15] = 0.0F;
	
	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_transpose(GAE_Matrix4_t* matrix) {
	GAE_Matrix4_t transpose;
	unsigned int row = 0U;
	unsigned int col = 0U;

	for (row = 0U; row < 4U; ++row) {
		for (col = 0U; col < 4U; ++col)
			transpose[ROWCOL(row, col, 4U)] = (*matrix)[ROWCOL(col, row, 4U)];
	}

	for (row = 0U; row < 16U; ++row)
		(*matrix)[row] = transpose[row];
	
	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_decompose(GAE_Matrix4_t* const matrix, GAE_Matrix3_t* rotation, GAE_Vector3_t* position) {
	GAE_Matrix4_getPosition(matrix, position);
	GAE_Matrix4_getRotation(matrix, rotation);

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_compose(GAE_Matrix4_t* matrix, GAE_Matrix3_t* const rotation, GAE_Vector3_t* const position) {
	GAE_Matrix4_setPosition(matrix, position);
	GAE_Matrix4_setRotation(matrix, rotation);

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_setPosition(GAE_Matrix4_t* matrix, GAE_Vector3_t* const position) {
	(*matrix)[ROWCOL(0U, 3U, 4U)] = (*position)[0];
	(*matrix)[ROWCOL(1U, 3U, 4U)] = (*position)[1];
	(*matrix)[ROWCOL(2U, 3U, 4U)] = (*position)[2];

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_setRotation(GAE_Matrix4_t* matrix, GAE_Matrix3_t* const rotation) {
	unsigned int row = 0U;
	unsigned int col = 0U;

	for (row = 0U; row < 3U; ++row) {
		for (col = 0U; col < 3U; ++col)
			(*matrix)[ROWCOL(row, col, 4U)] = (*rotation)[ROWCOL(row, col, 3U)];
	}

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_getPosition(GAE_Matrix4_t* const matrix, GAE_Vector3_t* position) {
	(*position)[0] = (*matrix)[ROWCOL(0U, 3U, 4U)];
	(*position)[1] = (*matrix)[ROWCOL(1U, 3U, 4U)];
	(*position)[2] = (*matrix)[ROWCOL(2U, 3U, 4U)];

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_getRotation(GAE_Matrix4_t* const matrix, GAE_Matrix3_t* rotation) {
	unsigned int row = 0U;
	unsigned int col = 0U;

	for (row = 0U; row < 3U; ++row) {
		for (col = 0U; col < 3U; ++col)
			(*rotation)[ROWCOL(row, col, 3U)] = (*matrix)[ROWCOL(row, col, 4U)];
	}

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_setScale(GAE_Matrix4_t* matrix, GAE_Vector3_t* const scale) {
	(*matrix)[ROWCOL(0U, 0U, 4U)] *= (*scale)[0];
	(*matrix)[ROWCOL(1U, 1U, 4U)] *= (*scale)[1];
	(*matrix)[ROWCOL(2U, 2U, 4U)] *= (*scale)[2];

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_add(GAE_Matrix4_t* matrix, GAE_Matrix4_t* const rhs) {
	unsigned int row = 0U;
	unsigned int col = 0U;

	for (row = 0U; row < 4U; ++row) {
		for (col = 0U; col < 4U; ++col)
			(*matrix)[ROWCOL(row, col, 4U)] += (*rhs)[ROWCOL(row, col, 4U)];
	}

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_sub(GAE_Matrix4_t* matrix, GAE_Matrix4_t* const rhs) {
	unsigned int row = 0U;
	unsigned int col = 0U;

	for (row = 0U; row < 4U; ++row) {
		for (col = 0U; col < 4U; ++col)
			(*matrix)[ROWCOL(row, col, 4U)] -= (*rhs)[ROWCOL(row, col, 4U)];
	}

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_mul(GAE_Matrix4_t* matrix, GAE_Matrix4_t* const rhs) {
	float newElement = 0.0F;
	unsigned int row = 0U;
	unsigned int col = 0U;
	unsigned int index = 0U;

	for (row = 0U; row < 4U; ++row) {
		for (col = 0U; col < 4U; ++col) {
			newElement = 0.0F;
			for (index = 0U; index < 4U; ++index)
				newElement += (*matrix)[ROWCOL(row, index, 4U)] * (*rhs)[ROWCOL(index, col, 4U)];
			(*matrix)[ROWCOL(row, col, 4U)] = newElement;
		}
	}

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_mulVec(GAE_Matrix4_t* matrix, const GAE_Vector_t rhs) {
	unsigned int index = 0U;

	for (index = 0U; index < 16U; ++index)
		(*matrix)[index] *= rhs;

	return matrix;
}

GAE_Matrix4_t* GAE_Matrix4_div(GAE_Matrix4_t* matrix, const GAE_Vector_t rhs) {
	const float inverse = 1.0F / rhs;
	unsigned int index = 0U;

	for (index = 0U; index < 16U; ++index)
		(*matrix)[index] *= inverse;

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_getFrontVector(GAE_Matrix3_t* const matrix, GAE_Vector3_t* vector) {
	(*vector)[0] = (*matrix)[2];
	(*vector)[1] = (*matrix)[5];
	(*vector)[2] = (*matrix)[8];

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_getRightVector(GAE_Matrix3_t* const matrix, GAE_Vector3_t* vector) {
	(*vector)[0] = (*matrix)[0];
	(*vector)[1] = (*matrix)[3];
	(*vector)[2] = (*matrix)[6];

	return matrix;	
}

GAE_Matrix3_t* GAE_Matrix3_getUpVector(GAE_Matrix3_t* const matrix, GAE_Vector3_t* vector) {
	(*vector)[0] = (*matrix)[1];
	(*vector)[1] = (*matrix)[4];
	(*vector)[2] = (*matrix)[7];

	return matrix;
}
GAE_Matrix3_t* GAE_Matrix3_setFrontVector(GAE_Matrix3_t* matrix, GAE_Vector3_t* const vector) {
	(*matrix)[2] = (*vector)[0];
	(*matrix)[5] = (*vector)[1];
	(*matrix)[8] = (*vector)[2];

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_setRightVector(GAE_Matrix3_t* matrix, GAE_Vector3_t* const vector) {
	(*matrix)[0] = (*vector)[0];
	(*matrix)[3] = (*vector)[1];
	(*matrix)[6] = (*vector)[2];

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_setUpVector(GAE_Matrix3_t* matrix, GAE_Vector3_t* const vector) {
	(*matrix)[2] = (*vector)[0];
	(*matrix)[5] = (*vector)[1];
	(*matrix)[8] = (*vector)[2];

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_setToIdentity(GAE_Matrix3_t* matrix) {
	GAE_Matrix3_setToZero(matrix);
	(*matrix)[0] = (*matrix)[4] = (*matrix)[8] = 1.0F;

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_setToZero(GAE_Matrix3_t* matrix) {
	(*matrix)[0] = (*matrix)[1] = (*matrix)[2] = (*matrix)[3] = (*matrix)[4] = (*matrix)[5] = (*matrix)[6] = (*matrix)[7] = (*matrix)[8] = 0.0F;

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_createXRotation(GAE_Matrix3_t* matrix, const float deg) {
	const float rad = GAE_DEG2RAD(deg);

	(*matrix)[0] = 1; (*matrix)[1] = 0; 		(*matrix)[2] = 0;
	(*matrix)[3] = 0; (*matrix)[4] = cos(rad); 	(*matrix)[5] = -sin(rad);
	(*matrix)[6] = 0; (*matrix)[7] = sin(rad);	(*matrix)[8] = cos(rad);

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_createYRotation(GAE_Matrix3_t* matrix, const float deg) {
	const float rad = GAE_DEG2RAD(deg);

	(*matrix)[0] = cos(rad); 	(*matrix)[1] = 0; 	(*matrix)[2] = sin(rad);
	(*matrix)[3] = 0; 			(*matrix)[4] = 1; 	(*matrix)[5] = 0;
	(*matrix)[6] = -sin(rad); 	(*matrix)[7] = 0;	(*matrix)[8] = cos(rad);

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_createZRotation(GAE_Matrix3_t* matrix, const float deg) {
	const float rad = GAE_DEG2RAD(deg);

	(*matrix)[0] = cos(rad); 	(*matrix)[1] = -sin(rad); 	(*matrix)[2] = 0;
	(*matrix)[3] = sin(rad); 	(*matrix)[4] = cos(rad); 	(*matrix)[5] = 0;
	(*matrix)[6] = 0; 			(*matrix)[7] = 0;			(*matrix)[8] = 1;

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_add(GAE_Matrix3_t* matrix, GAE_Matrix3_t* const rhs) {
	unsigned int row = 0U;
	unsigned int col = 0U;

	for (row = 0U; row < 3U; ++row) {
		for (col = 0U; col < 3U; ++col)
			(*matrix)[ROWCOL(row, col, 3U)] += (*rhs)[ROWCOL(row, col, 3U)];
	}

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_sub(GAE_Matrix3_t* matrix, GAE_Matrix3_t* const rhs) {
	unsigned int row = 0U;
	unsigned int col = 0U;

	for (row = 0U; row < 3U; ++row) {
		for (col = 0U; col < 3U; ++col)
			(*matrix)[ROWCOL(row, col, 3U)] -= (*rhs)[ROWCOL(row, col, 3U)];
	}

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_mul(GAE_Matrix3_t* matrix, GAE_Matrix3_t* const rhs) {
	float newElement = 0.0F;
	unsigned int row = 0U;
	unsigned int col = 0U;
	unsigned int index = 0U;

	for (row = 0U; row < 3U; ++row) {
		for (col = 0U; col < 3U; ++col) {
			newElement = 0.0F;
			for (index = 0U; index < 3U; ++index)
				newElement += (*matrix)[ROWCOL(row, index, 3U)] * (*rhs)[ROWCOL(index, col, 3U)];
			(*matrix)[ROWCOL(row, col, 3U)] = newElement;
		}
	}

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_mulVec(GAE_Matrix3_t* matrix, const GAE_Vector_t rhs) {
	unsigned int index = 0U;

	for (index = 0U; index < 9U; ++index)
		(*matrix)[index] *= rhs;

	return matrix;
}

GAE_Matrix3_t* GAE_Matrix3_div(GAE_Matrix3_t* matrix, const GAE_Vector_t rhs) {
	const float inverse = 1.0F / rhs;
	unsigned int index = 0U;

	for (index = 0U; index < 9U; ++index)
		(*matrix)[index] *= inverse;

	return matrix;
}

GAE_Matrix2_t* GAE_Matrix2_setToIdentity(GAE_Matrix2_t* matrix) {
	GAE_Matrix2_setToZero(matrix);
	(*matrix)[0] = (*matrix)[2] = 1.0F;

	return matrix;
}

GAE_Matrix2_t* GAE_Matrix2_setToZero(GAE_Matrix2_t* matrix) {
	(*matrix)[0] = (*matrix)[1] = (*matrix)[2] = (*matrix)[3] = 0.0F;

	return matrix;
}

GAE_Matrix2_t* GAE_Matrix2_add(GAE_Matrix2_t* matrix, GAE_Matrix2_t* const rhs) {
	unsigned int row = 0U;
	unsigned int col = 0U;

	for (row = 0U; row < 2U; ++row) {
		for (col = 0U; col < 2U; ++col)
			(*matrix)[ROWCOL(row, col, 2U)] += (*rhs)[ROWCOL(row, col, 2U)];
	}

	return matrix;
}

GAE_Matrix2_t* GAE_Matrix2_sub(GAE_Matrix2_t* matrix, GAE_Matrix2_t* const rhs) {
	unsigned int row = 0U;
	unsigned int col = 0U;

	for (row = 0U; row < 2U; ++row) {
		for (col = 0U; col < 2U; ++col)
			(*matrix)[ROWCOL(row, col, 2U)] -= (*rhs)[ROWCOL(row, col, 2U)];
	}

	return matrix;
}

GAE_Matrix2_t* GAE_Matrix2_mul(GAE_Matrix2_t* matrix, GAE_Matrix2_t* const rhs) {
	float newElement = 0.0F;
	unsigned int row = 0U;
	unsigned int col = 0U;
	unsigned int index = 0U;

	for (row = 0U; row < 2U; ++row) {
		for (col = 0U; col < 2U; ++col) {
			newElement = 0.0F;
			for (index = 0U; index < 2U; ++index)
				newElement += (*matrix)[ROWCOL(row, index, 2U)] * (*rhs)[ROWCOL(index, col, 2U)];
			(*matrix)[ROWCOL(row, col, 2U)] = newElement;
		}
	}

	return matrix;
}

GAE_Matrix2_t* GAE_Matrix2_mulVec(GAE_Matrix2_t* matrix, const GAE_Vector_t rhs) {
	unsigned int index = 0U;

	for (index = 0U; index < 4U; ++index)
		(*matrix)[index] *= rhs;

	return matrix;
}

GAE_Matrix2_t* GAE_Matrix2_div(GAE_Matrix2_t* matrix, const GAE_Vector_t rhs) {
	const float inverse = 1.0F / rhs;
	unsigned int index = 0U;

	for (index = 0U; index < 4U; ++index)
		(*matrix)[index] *= inverse;

	return matrix;
}
