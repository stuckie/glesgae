#ifndef _RECT_H_
#define _RECT_H_

typedef struct GAE_Rect_s {
    int x, y, w, h;
} GAE_Rect_t;

/* Create a new Rect construct with the given x, y, w and h */
GAE_Rect_t* GAE_Rect_create(int x, int y, int w, int h);

/* Delete a Rect construct */
void GAE_Rect_delete(GAE_Rect_t* rect);

#endif
