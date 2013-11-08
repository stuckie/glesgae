#ifndef _MATERIAL_H_
#define _MATERIAL_H_

struct GAE_Shader_s;
struct GAE_Array_s;
struct GAE_Texture_s;

typedef struct GAE_Material_s {
	struct GAE_Shader_s* shader;
	struct GAE_Array_s* textures;
} GAE_Material_t;

GAE_Material_t* GAE_Material_create(void);
GAE_Material_t* GAE_Material_addTexture(GAE_Material_t* material, struct GAE_Texture_s* const texture);
struct GAE_Array_s* GAE_Material_textures(GAE_Material_t* material);
void GAE_Material_delete(GAE_Material_t* material);

#endif

