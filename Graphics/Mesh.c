#include "Mesh.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"

#include <stdlib.h>

GAE_Mesh_t* GAE_Mesh_create(GAE_VertexBuffer_t* const vBuffer, GAE_IndexBuffer_t* const iBuffer, GAE_Material_t* const material) {
	GAE_Mesh_t* mesh = malloc(sizeof(GAE_Mesh_t));

	mesh->vBuffer = vBuffer;
	mesh->iBuffer = iBuffer;
	mesh->material = material;

	return mesh;
}

void GAE_Mesh_delete(GAE_Mesh_t* mesh) {
	free(mesh);
	mesh = 0;
}
