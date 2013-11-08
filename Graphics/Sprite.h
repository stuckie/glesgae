#ifndef _SPRITE_H_
#define _SPRITE_H_

#if defined(SDL2)
#include "Sprite/SDL2/Sprite.h"
#elif defined(GLX)
#include "Sprite/3D/Sprite.h"
#endif

#endif
