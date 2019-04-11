#ifndef _ANIMATION_H_
#define _ANIMATION_H_

struct GAE_ArrayList_s;
struct GAE_Frame_s;

typedef struct GAE_Animation_s {
	struct GAE_ArrayList_s* frames;
	float speed;
} GAE_Animation_t;

/* Create a new animation */
GAE_Animation_t* GAE_Animation_create();

/* Add a frame to the given Animation */
GAE_Animation_t* GAE_Animation_addFrame(GAE_Animation_t* animation, struct GAE_Frame_s* frame);

/* Delete an animation */
void GAE_Animation_delete(GAE_Animation_t* animation);

#endif

