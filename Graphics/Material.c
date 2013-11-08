#include "Material.h"

#include "Texture.h"
#include "../Utils/Array.h"

GAE_Material_t* GAE_Material_create(void) {
	GAE_Material_t* material = malloc(sizeof(GAE_Material_t));

	material->shader = 0;
	material->textures = GAE_Array_create(sizeof(GAE_Texture_t));

	return material;
}

GAE_Material_t* GAE_Material_addTexture(GAE_Material_t* material, GAE_Texture_t* const texture) {
	GAE_Array_push(material->textures, texture);
	return material;
}

GAE_Array_t* GAE_Material_textures(GAE_Material_t* material) {
	return material->textures;
}

void GAE_Material_delete(GAE_Material_t* material) {
	GAE_Array_delete(material->textures);
	free(material);
	material = 0;
}
