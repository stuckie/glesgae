#ifndef _SPRITE_H_
#define _SPRITE_H_

struct GAE_ArrayList_s;
struct GAE_Frame_s;
struct GAE_Rect_s;

typedef struct GAE_Sprite_s {
    struct GAE_ArrayList_s* frames;     /* Array of frames */
    struct GAE_Rect_s* dest;            /* Where we're going to draw on the screen */
    float animSpeed;                    /* Frames Per Second */
    float currentFrame;                 /* Current Frame */
} GAE_Sprite_t;

/* Create a new Sprite object */
GAE_Sprite_t* GAE_Sprite_create(int width, int height);

/* Add a frame to the given Sprite - takes ownership of it and deletes it in Sprite_delete */
GAE_Sprite_t* GAE_Sprite_addFrame(GAE_Sprite_t* sprite, struct GAE_Frame_s* frame);

/* Gets the current frame */
struct GAE_Frame_s* GAE_Sprite_getFrame(GAE_Sprite_t* sprite);

/* Updates the sprite w.r.t delta time */
GAE_Sprite_t* GAE_Sprite_update(GAE_Sprite_t* sprite, float deltaTime);

/* Delete a sprite object */
void GAE_Sprite_delete(GAE_Sprite_t* sprite);

#endif
