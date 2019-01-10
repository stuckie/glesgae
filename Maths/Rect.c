#include "Rect.h"

#include <stdlib.h>

GAE_Rect_t* GAE_Rect_create(int x, int y, int w, int h)
{
    GAE_Rect_t* rect = (GAE_Rect_t*)malloc(sizeof(GAE_Rect_t));
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;

    return rect;
}

void GAE_Rect_delete(GAE_Rect_t* rect)
{
    free(rect);
}
