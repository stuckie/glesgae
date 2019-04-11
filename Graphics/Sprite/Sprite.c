#include "Sprite.h"
#include "Frame.h"
#include "Animation.h"

#include "../../Maths/Rect.h"
#include "../../Utils/ArrayList.h"

#include <math.h>

GAE_Sprite_t* GAE_Sprite_create(int width, int height)
{
    GAE_Sprite_t* sprite = malloc(sizeof(GAE_Sprite_t));
    sprite->anim = 0;
    sprite->currentFrame = 0.0F;
    sprite->dest = GAE_Rect_create(0, 0, width, height);

    return sprite;
}

GAE_Sprite_t* GAE_Sprite_setAnimation(GAE_Sprite_t* sprite, struct GAE_Animation_s* anim)
{
	sprite->anim = anim;
	return sprite;
}

GAE_Sprite_t* GAE_Sprite_getFrame(GAE_Sprite_t* sprite, GAE_Frame_t** outFrame)
{
	if (0 == sprite->anim) outFrame = 0;
	else (*outFrame) = *(GAE_Frame_t**)GAE_ArrayList_get(sprite->anim->frames, (unsigned int)floor(sprite->currentFrame) % GAE_ArrayList_length(sprite->anim->frames));
    return sprite;
}

GAE_Sprite_t* GAE_Sprite_update(GAE_Sprite_t* sprite, float deltaTime)
{
	if (0 != sprite->anim) {
		float nextFrame = sprite->currentFrame + (deltaTime * sprite->anim->speed);
		const unsigned int lastFrame = GAE_ArrayList_length(sprite->anim->frames);

		unsigned int mod = (unsigned int)floor(nextFrame) % lastFrame;
		nextFrame = (float)mod + (nextFrame - floor(nextFrame));

		sprite->currentFrame = nextFrame;
	}

    return sprite;
}

void GAE_Sprite_delete(GAE_Sprite_t* sprite)
{
    free(sprite);
    sprite = 0;
}
