#ifndef _SPRITE_H_
#define _SPRITE_H_

struct GAE_Frame_s;
struct GAE_Rect_s;
struct GAE_Animation_s;

typedef struct GAE_Sprite_s {
    struct GAE_Animation_s* anim;		/* Current Animation */
    struct GAE_Rect_s* dest;            /* Where we're going to draw on the screen */
    float currentFrame;                 /* Current Frame */
} GAE_Sprite_t;

/* Create a new Sprite object */
GAE_Sprite_t* GAE_Sprite_create(int width, int height);

/* Sets the current animation */
GAE_Sprite_t* GAE_Sprite_setAnimation(GAE_Sprite_t* sprite, struct GAE_Animation_s* anim);

/* Gets the current frame */
GAE_Sprite_t* GAE_Sprite_getFrame(GAE_Sprite_t* sprite, struct GAE_Frame_s** outAnim);

/* Updates the sprite w.r.t delta time */
GAE_Sprite_t* GAE_Sprite_update(GAE_Sprite_t* sprite, float deltaTime);

/* Delete a sprite object */
void GAE_Sprite_delete(GAE_Sprite_t* sprite);

#endif
