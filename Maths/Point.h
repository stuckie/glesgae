#ifndef _POINT_H_
#define _POINT_H_

#include "../GAE_Types.h"

struct GAE_Rect_s;

GAE_BOOL GAE_PointInRect(GAE_Point2D_t* point, struct GAE_Rect_s* rect);

#endif
