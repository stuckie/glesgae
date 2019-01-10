#include "Frame.h"
#include "../Texture.h"
#include "../../Maths/Rect.h"

#include <stdlib.h>

GAE_Frame_t* GAE_Frame_create(GAE_Texture_t* texture, int x, int y, int w, int h)
{
    GAE_Frame_t* frame = (GAE_Frame_t*)malloc(sizeof(GAE_Frame_t));
    frame->texture = texture;
    frame->rect = GAE_Rect_create(x, y, w, h);
    
    return frame;
}

void GAE_Frame_delete(GAE_Frame_t* frame)
{
    if (0 == frame) return;

    GAE_Rect_delete(frame->rect);
    free(frame);
    frame = 0;
}
