#ifndef _GLESGAE_TYPES_H_
#define _GLESGAE_TYPES_H_

#include <stdint.h>

extern const unsigned int GAE_INVALID;

#define GAE_UNUSED(x) {(void)(x);}
#define GAE_TRUE 1
#define GAE_FALSE 0

#define GAE_PI 3.14159265358979323846F
#define GAE_DEG2RAD(x) (x * GAE_PI / 180.0F)
#define GAE_RAD2DEG(x) (x * 180.0F / GAE_PI)

#define GAE_MIN(a, b)	((a) < (b) ? (a) : (b))
#define GAE_MAX(a, b)	((a) > (b) ? (a) : (b))

#define GAE_LERP(a, b, time)			( (a) + (time) * (float) ((b) - (a)) )
#define GAE_CLAMP(val, low, hi)			((val) < (low) ? (low) : (val) > (hi) ? (hi) : (val))

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

typedef float GAE_Point_t;				/* point in time */
typedef GAE_Point_t GAE_Point2D_t[2];	/* x, y point - could be GAE_Vector2_t but sometimes nice to be specific */
typedef GAE_Point_t GAE_Point3D_t[3];	/* x, y, z point - could be GAE_Vector3_t but sometimes nice to be specific */

#endif

