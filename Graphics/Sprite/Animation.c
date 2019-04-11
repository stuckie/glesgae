#include "Animation.h"
#include "Frame.h"

#include "../../Utils/ArrayList.h"

GAE_Animation_t* GAE_Animation_create()
{
	GAE_Animation_t* anim = malloc(sizeof(GAE_Animation_t));
    anim->frames = GAE_ArrayList_create(sizeof(GAE_Frame_t*)); /* Yes, pointer */
    
	return anim;
}

GAE_Animation_t* GAE_Animation_addFrame(GAE_Animation_t* anim, GAE_Frame_t* frame)
{
    GAE_ArrayList_push(anim->frames, &frame);
    return anim;
}

void GAE_Animation_delete(GAE_Animation_t* anim)
{
	unsigned int i = 0U;
    unsigned int size = GAE_ArrayList_length(anim->frames);

    for (i = 0U; i < size; ++i) {
        GAE_Frame_t* frame = *(GAE_Frame_t**)GAE_ArrayList_get(anim->frames, i);
        GAE_Frame_delete(frame);
    }

    GAE_ArrayList_delete(anim->frames);
    
    free(anim);
    anim = 0;
}

