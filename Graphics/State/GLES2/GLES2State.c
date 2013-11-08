#include "GLES2State.h"

#include "../../Camera.h"
#include "../../Shader.h"
#include "../../Material.h"
#include "../../Texture.h"
#include "../../../Maths/Matrix.h"
#include "../../../GAE_Types.h"
#include "../../../Utils/Array.h"
#include "../../../Utils/Map.h"
#include "../../../Utils/HashString.h"

#include <stdlib.h>
#include <assert.h>

static GAE_HashString_t aPositionHS = 0;
static GAE_HashString_t aColourHS = 0;
static GAE_HashString_t aNormalHS = 0;
static GAE_HashString_t aTexCoord0HS = 0;
static GAE_HashString_t aTexCoord1HS = 0;
static GAE_HashString_t aCustom0HS = 0;
static GAE_HashString_t aCustom1HS = 0;
static GAE_HashString_t aCustom2HS = 0;

void resetAttributes(GAE_RenderState_GLES2_t* state);

GAE_RenderState_t* GAE_RenderState_create(void) {
	GAE_RenderState_GLES2_t* state = malloc(sizeof(GAE_RenderState_GLES2_t));
	GAE_RenderState_t* parent = malloc(sizeof(GAE_RenderState_t));

	if (0 == aPositionHS)
		aPositionHS = GAE_HashString_create("a_position");
	if (0 == aColourHS)
		aColourHS = GAE_HashString_create("a_color");
	if (0 == aNormalHS)
		aNormalHS = GAE_HashString_create("a_normal");
	if (0 == aTexCoord0HS)
		aTexCoord0HS = GAE_HashString_create("a_texCoord0");
	if (0 == aTexCoord1HS)
		aTexCoord1HS = GAE_HashString_create("a_texCoord1");
	if (0 == aCustom0HS)
		aCustom0HS = GAE_HashString_create("a_custom0");
	if (0 == aCustom1HS)
		aCustom1HS = GAE_HashString_create("a_custom1");
	if (0 == aCustom2HS)
		aCustom2HS = GAE_HashString_create("a_custom2");

	parent->camera = 0;
	parent->isTexturingEnabled = GAE_FALSE;
	parent->isAlphaBlendingEnabled = GAE_FALSE;

	state->textureMatrix = 0;
	state->currentShader = 0;
	state->a_position = GL_INVALID_VALUE;
	state->a_colour = GL_INVALID_VALUE;
	state->a_normal = GL_INVALID_VALUE;
	state->a_texCoord0 = GL_INVALID_VALUE;
	state->a_texCoord1 = GL_INVALID_VALUE;
	state->a_custom0 = GL_INVALID_VALUE;
	state->a_custom1 = GL_INVALID_VALUE;
	state->a_custom2 = GL_INVALID_VALUE;

	state->lastTexture = 0;
	state->lastTextureUnit = GL_INVALID_VALUE;

	state->uniformUpdaters = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(GAE_Shader_UniformUpdater_t), GAE_HashString_compare);

	parent->platform = (void*)state;

	return parent;
}

void GAE_RenderState_delete(GAE_RenderState_t* state) {
	GAE_RenderState_GLES2_t* platform = (GAE_RenderState_GLES2_t*)state->platform;

	GAE_Map_delete(platform->uniformUpdaters);
	free(platform);
	free(state);
	state = 0;
}

GAE_RenderState_t* GAE_RenderState_setTexturingEnabled(GAE_RenderState_t* state, const GAE_BOOL isEnabled) {
	if (GAE_TRUE == isEnabled) {
		if (GAE_FALSE == state->isTexturingEnabled) {
			glEnable(GL_TEXTURE_2D);
			state->isTexturingEnabled = GAE_TRUE;
		}
	} else {
		if (GAE_TRUE == state->isTexturingEnabled) {
			glDisable(GL_TEXTURE_2D);
			state->isTexturingEnabled = GAE_FALSE;
		}
	}

	return state;
}

GAE_RenderState_t* GAE_RenderState_setAlphaBlendingEnabled(GAE_RenderState_t* state, const GAE_BOOL isEnabled) {
	if (GAE_TRUE == isEnabled) {
		if (GAE_FALSE == state->isAlphaBlendingEnabled) {
			glEnable(GL_BLEND);
			state->isAlphaBlendingEnabled = GAE_TRUE;
		}
	} else {
		if (GAE_TRUE == state->isAlphaBlendingEnabled) {
			glDisable(GL_BLEND);
			state->isAlphaBlendingEnabled = GAE_FALSE;
		}
	}

	return state;
}

GAE_RenderState_t* GAE_RenderState_setBlendingFunction(GAE_RenderState_t* state, const GLenum source, const GLenum destination) {
	glBlendFunc(source, destination);
	return state;
}

GAE_RenderState_t* GAE_RenderState_setFullBlendingFunction(GAE_RenderState_t* state, const GLenum sourceRGB, const GLenum destinationRGB
																					,const GLenum sourceAlpha, const GLenum destinationAlpha) {
	glBlendFuncSeparate(sourceRGB, destinationRGB, sourceAlpha, destinationAlpha);
	return state;
}

GAE_RenderState_t* GAE_RenderState_addUniformUpdater(GAE_RenderState_t* state, const GAE_HashString_t uniformName, GAE_Shader_UniformUpdater_t updater) {
	GAE_RenderState_GLES2_t* platform = (GAE_RenderState_GLES2_t*)state->platform;
	GAE_Map_push(platform->uniformUpdaters, (void*)&uniformName, (void*)&updater);
	return state;
}

GAE_RenderState_t* GAE_RenderState_bindShader(GAE_RenderState_t* state, GAE_Shader_t* const shader) {
	GAE_RenderState_GLES2_t* platform = (GAE_RenderState_GLES2_t*)state->platform;
	assert(0 != shader);
	if (platform->currentShader != shader) {
		platform->currentShader = shader;
		glUseProgram(shader->program);
		resetAttributes(platform);
/*		
//		const std::vector<std::pair<HashString, GLint> >& attributes(shader->getAttributeArray());
//		for (std::vector<std::pair<HashString, GLint> >::const_iterator itr(attributes.begin()); itr < attributes.end(); ++itr)
//			glEnableVertexAttribArray(itr->second);
*/
	}

	return state;
}

void resetAttributes(GAE_RenderState_GLES2_t* state) {
	state->a_position = GL_INVALID_VALUE;
	state->a_colour = GL_INVALID_VALUE;
	state->a_normal = GL_INVALID_VALUE;
	state->a_texCoord0 = GL_INVALID_VALUE;
	state->a_texCoord1 = GL_INVALID_VALUE;
	state->a_custom0 = GL_INVALID_VALUE;
	state->a_custom1 = GL_INVALID_VALUE;
	state->a_custom2 = GL_INVALID_VALUE;

	if (0 != state->currentShader) {
		state->a_position = GAE_Shader_getAttribute(state->currentShader, aPositionHS);
		state->a_colour = GAE_Shader_getAttribute(state->currentShader, aColourHS);
		state->a_normal = GAE_Shader_getAttribute(state->currentShader, aNormalHS);
		state->a_texCoord0 = GAE_Shader_getAttribute(state->currentShader, aTexCoord0HS);
		state->a_texCoord1 = GAE_Shader_getAttribute(state->currentShader, aTexCoord1HS);
		state->a_custom0 = GAE_Shader_getAttribute(state->currentShader, aCustom0HS);
		state->a_custom1 = GAE_Shader_getAttribute(state->currentShader, aCustom1HS);
		state->a_custom2 = GAE_Shader_getAttribute(state->currentShader, aCustom2HS);
	}

	if (GL_INVALID_VALUE != state->a_position)
		glEnableVertexAttribArray(state->a_position);
	if (GL_INVALID_VALUE != state->a_colour)
		glEnableVertexAttribArray(state->a_colour);
	if (GL_INVALID_VALUE != state->a_normal)
		glEnableVertexAttribArray(state->a_normal);
	if (GL_INVALID_VALUE != state->a_texCoord0)
		glEnableVertexAttribArray(state->a_texCoord0);
	if (GL_INVALID_VALUE != state->a_texCoord1)
		glEnableVertexAttribArray(state->a_texCoord1);
	if (GL_INVALID_VALUE != state->a_custom0)
		glEnableVertexAttribArray(state->a_custom0);
	if (GL_INVALID_VALUE != state->a_custom1)
		glEnableVertexAttribArray(state->a_custom1);
	if (GL_INVALID_VALUE != state->a_custom2)
		glEnableVertexAttribArray(state->a_custom2);
}

GAE_RenderState_t* GAE_RenderState_updateUniforms(GAE_RenderState_t* state, GAE_Material_t* const material, GAE_Matrix4_t* const transform) {
	GAE_RenderState_GLES2_t* platform = (GAE_RenderState_GLES2_t*)state->platform;
	GAE_Shader_UniformUpdater_t* arrayBegin = (GAE_Shader_UniformUpdater_t*)GAE_Map_begin(platform->uniformUpdaters);
	GAE_Shader_UniformUpdater_t* updater = 0;
	GAE_HashString_t* idsBegin = (GAE_HashString_t*)GAE_Map_ids(platform->uniformUpdaters);
	GAE_HashString_t* id = 0;
	const unsigned int arraySize = GAE_Map_size(platform->uniformUpdaters);
	unsigned int index = 0;

	while (index < arraySize) {
		updater = arrayBegin + index;
		id = idsBegin + index;
		(*updater)(GAE_Shader_getUniform(platform->currentShader, *id), state->camera, material, transform);
		++index;
	}

	return state;
}

GAE_RenderState_t* GAE_RenderState_updateTextures(GAE_RenderState_t* state, GAE_Material_t* const material) {
	const unsigned int textureCount = GAE_Array_size(material->textures);
	GAE_RenderState_GLES2_t* platform = (GAE_RenderState_GLES2_t*)state->platform;
	unsigned int index = 0U;
	GLenum currentUnit = GL_INVALID_VALUE;
	GAE_Texture_t* texture;

	for (index = 0U; index < textureCount; ++index) {
		currentUnit = GL_TEXTURE0 + index;
		if (currentUnit != platform->lastTextureUnit) {
			glActiveTexture(currentUnit);
			platform->lastTextureUnit = currentUnit;
		}
		
		texture = (GAE_Texture_t*)GAE_Array_get(material->textures, index);
		if (texture != platform->lastTexture) {
			GAE_GL_Texture_t* glTexture = (GAE_GL_Texture_t*)texture->platform;
			platform->lastTexture = texture;
			glBindTexture(GL_TEXTURE_2D, glTexture->id);
		}
	}

	return state;
}
