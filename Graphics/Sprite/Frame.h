#ifndef _FRAME_H_
#define _FRAME_H_

struct GAE_Texture_s;
struct GAE_Rect_s;

typedef struct GAE_Frame_s {
    struct GAE_Texture_s* texture;
    struct GAE_Rect_s* rect;
} GAE_Frame_t;

GAE_Frame_t* GAE_Frame_create(struct GAE_Texture_s* texture, int x, int y, int w, int h);
void GAE_Frame_delete(GAE_Frame_t* frame);

#endif
