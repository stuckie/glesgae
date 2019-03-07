#include "Sprite.h"
#include "Frame.h"

#include "../../Maths/Rect.h"
#include "../../Utils/ArrayList.h"

#include <math.h>

GAE_Sprite_t* GAE_Sprite_create(int width, int height)
{
    GAE_Sprite_t* sprite = malloc(sizeof(GAE_Sprite_t));
    sprite->frames = GAE_ArrayList_create(sizeof(GAE_Frame_t*)); /* Yes, pointer */
    sprite->animSpeed = 0.0F;
    sprite->currentFrame = 0.0F;
    sprite->dest = GAE_Rect_create(0, 0, width, height);

    return sprite;
}

GAE_Sprite_t* GAE_Sprite_addFrame(GAE_Sprite_t* sprite, GAE_Frame_t* frame)
{
    GAE_ArrayList_push(sprite->frames, &frame);
    return sprite;
}

GAE_Frame_t* GAE_Sprite_getFrame(GAE_Sprite_t* sprite)
{
    return *(GAE_Frame_t**)GAE_ArrayList_get(sprite->frames, (unsigned int)floor(sprite->currentFrame));
}

GAE_Sprite_t* GAE_Sprite_update(GAE_Sprite_t* sprite, float deltaTime)
{    
    float nextFrame = sprite->currentFrame + (deltaTime * sprite->animSpeed);
    const unsigned int lastFrame = GAE_ArrayList_length(sprite->frames);

    unsigned int mod = (unsigned int)floor(nextFrame) % lastFrame;
    nextFrame = (float)mod + (nextFrame - floor(nextFrame));

    sprite->currentFrame = nextFrame;

    return sprite;
}

void GAE_Sprite_delete(GAE_Sprite_t* sprite)
{
    unsigned int i = 0U;
    unsigned int size = GAE_ArrayList_length(sprite->frames);

    for (i = 0U; i < size; ++i) {
        GAE_Frame_t* frame = *(GAE_Frame_t**)GAE_ArrayList_get(sprite->frames, i);
        GAE_Frame_delete(frame);
    }

    GAE_ArrayList_delete(sprite->frames);
    free(sprite);
    sprite = 0;
}
