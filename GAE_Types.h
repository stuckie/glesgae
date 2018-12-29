#ifndef _GLESGAE_TYPES_H_
#define _GLESGAE_TYPES_H_

extern const unsigned int GAE_INVALID;

#define GAE_UNUSED(x) {(void)(x);}
#define GAE_TRUE 1
#define GAE_FALSE 0

#define GAE_PI 3.1415926535
#define GAE_DEG2RAD(x) (x * GAE_PI / 180.0)
#define GAE_RAD2DEG(x) (x * 180.0 / GAE_PI)

typedef unsigned int GAE_HashString_t;
typedef unsigned int GAE_EntityId_t;
typedef GAE_HashString_t GAE_ComponentType_t;

typedef int GAE_BOOL;
typedef unsigned char GAE_BYTE;
typedef float GAE_Vector_t;

typedef GAE_Vector_t GAE_Vector2_t[2];
typedef GAE_Vector_t GAE_Vector3_t[3];
typedef GAE_Vector_t GAE_Vector4_t[4];

typedef GAE_Vector_t GAE_Matrix2_t[4];
typedef GAE_Vector_t GAE_Matrix3_t[9];
typedef GAE_Vector_t GAE_Matrix4_t[16];

#endif

