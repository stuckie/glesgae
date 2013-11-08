#ifndef _SHADER_GL_VBO_RENDERER_H_
#define _SHADER_GL_VBO_RENDERER_H_

#include "../../../GAE_Types.h"

struct GAE_VertexBuffer_s;
struct GAE_IndexBuffer_s;
struct GAE_Texture_s;
struct GAE_RenderState_s;
struct GAE_Mesh_s;
struct GAE_Sprite_s;

typedef struct GAE_Renderer_s {
	struct GAE_VertexBuffer_s* lastVertexBuffer;
	struct GAE_IndexBuffer_s* lastIndexBuffer;
	struct GAE_Texture_s* lastTexture;
	struct GAE_RenderState_s* state;
} GAE_Renderer_t;

GAE_Renderer_t* GAE_Renderer_create(void);
GAE_Renderer_t* GAE_Renderer_drawMesh(GAE_Renderer_t* renderer, struct GAE_Mesh_s* const mesh, GAE_Matrix4_t* const transform);
GAE_Renderer_t* GAE_Renderer_drawSprite(GAE_Renderer_t* renderer, struct GAE_Sprite_s* const sprite);
void GAE_Renderer_delete(GAE_Renderer_t* renderer);

#endif
