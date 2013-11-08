#ifndef _GLES2_STATE_H_
#define _GLES2_STATE_H_

#if defined(GLX)
	#include "../../Context/GLX/GLee.h"
#elif defined(PANDORA) || defined(ANDROID)
	#if defined(GLES1)
		#include <GLES/gl.h>
	#elif defined(GLES2)
		#include <GLES2/gl2.h>
	#endif
#endif

#include "../RenderState.h"
#include "../../Shader.h"
#include "../../../GAE_Types.h"

struct GAE_Texture_s;
struct GAE_Map_s;
struct GAE_Material_s;

typedef struct GAE_RenderState_GLES2_s {
	GAE_Matrix4_t* textureMatrix;
	GAE_Shader_t* currentShader;

	GLuint a_position;
	GLuint a_colour;
	GLuint a_normal;
	GLuint a_texCoord0;
	GLuint a_texCoord1;
	GLuint a_custom0;
	GLuint a_custom1;
	GLuint a_custom2;

	struct GAE_Texture_s* lastTexture;
	GLenum lastTextureUnit;

	struct GAE_Map_s* uniformUpdaters;
} GAE_RenderState_GLES2_t;

GAE_RenderState_t* GAE_RenderState_create(void);
void GAE_RenderState_delete(GAE_RenderState_t* state);
GAE_RenderState_t* GAE_RenderState_setTexturingEnabled(GAE_RenderState_t* state, const GAE_BOOL isEnabled);
GAE_RenderState_t* GAE_RenderState_setAlphaBlendingEnabled(GAE_RenderState_t* state, const GAE_BOOL isEnabled);
GAE_RenderState_t* GAE_RenderState_setBlendingFunction(GAE_RenderState_t* state, const GLenum source, const GLenum destination);
GAE_RenderState_t* GAE_RenderState_setFullBlendingFunction(GAE_RenderState_t* state, const GLenum sourceRGB, const GLenum destinationRGB
																								,const GLenum sourceAlpha, const GLenum destinationAlpha);
GAE_RenderState_t* GAE_RenderState_addUniformUpdater(GAE_RenderState_t* state, const GAE_HashString_t uniformName, GAE_Shader_UniformUpdater_t updater);
GAE_RenderState_t* GAE_RenderState_updateUniforms(GAE_RenderState_t* state, struct GAE_Material_s* const material, GAE_Matrix4_t* const transform);
GAE_RenderState_t* GAE_RenderState_updateTextures(GAE_RenderState_t* state, struct GAE_Material_s* const material);
GAE_RenderState_t* GAE_RenderState_bindShader(GAE_RenderState_t* state, GAE_Shader_t* const shader);

#endif
