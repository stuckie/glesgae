#ifndef _SHADER_H_
#define _SHADER_H_

#include "../GAE_Types.h"

struct GAE_Map_s;
struct GAE_Camera_s;
struct GAE_Material_s;
struct GAE_File_s;

typedef void (*GAE_Shader_UniformUpdater_t)(const int uniformId, struct GAE_Camera_s* const camera, struct GAE_Material_s* const material, GAE_Matrix4_t* const transform);

typedef struct GAE_Shader_s {
	struct GAE_Map_s* uniforms;
	struct GAE_Map_s* attributes;
	unsigned int vertex;
	unsigned int fragment;
	unsigned int program;
} GAE_Shader_t;

GAE_Shader_t* GAE_Shader_create(struct GAE_File_s* const vertex, struct GAE_File_s* const fragment);
void GAE_Shader_delete(GAE_Shader_t* shader);
int GAE_Shader_getAttribute(GAE_Shader_t* const shader, const GAE_HashString_t id);
int GAE_Shader_getUniform(GAE_Shader_t* const shader, const GAE_HashString_t id);

#endif
