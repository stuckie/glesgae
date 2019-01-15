#include "Point.h"

#include "Rect.h"

GAE_BOOL GAE_PointInRect(GAE_Point2D_t* point, GAE_Rect_t* rect)
{
	return (((*point)[0] > rect->x && (*point)[0] < rect->x + rect->w)
		&& ((*point)[1] > rect->y && (*point)[1] < rect->y + rect->h));
}

