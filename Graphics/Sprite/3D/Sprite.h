#ifndef _3D_SPRITE_H_
#define _3D_SPRITE_H_

#include "../../../GAE_Types.h"

struct GAE_Mesh_s;

typedef struct GAE_Sprite_s {
	GAE_Matrix4_t transform;
	struct GAE_Mesh_s* mesh;
} GAE_Sprite_t;

GAE_Sprite_t* GAE_Sprite_create(const char* texturePath);
void GAE_Sprite_delete(GAE_Sprite_t* sprite);

#endif
