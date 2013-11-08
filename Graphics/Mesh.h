#ifndef _MESH_H_
#define _MESH_H_

struct GAE_VertexBuffer_s;
struct GAE_IndexBuffer_s;
struct GAE_Material_s;

typedef struct GAE_Mesh_s {
	struct GAE_VertexBuffer_s* vBuffer;
	struct GAE_IndexBuffer_s* iBuffer;
	struct GAE_Material_s* material;
} GAE_Mesh_t;

GAE_Mesh_t* GAE_Mesh_create(struct GAE_VertexBuffer_s* const vBuffer, struct GAE_IndexBuffer_s* const iBuffer, struct GAE_Material_s* const material);
void GAE_Mesh_delete(GAE_Mesh_t* mesh);

#endif
