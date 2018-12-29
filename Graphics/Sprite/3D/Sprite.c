#include "../../Sprite.h"

#include "../../Mesh.h"
#include "../../VertexBuffer.h"
#include "../../IndexBuffer.h"
#include "../../Material.h"
#include "../../Texture.h"
#include "../../Shader.h"
#include "../../../Maths/Matrix.h"
#include "../../../File/File.h"

#include <stdlib.h>
#include <string.h>

GAE_Sprite_t* GAE_Sprite_create(const char* texturePath) {
	GAE_Sprite_t* sprite = malloc(sizeof(GAE_Sprite_t));

	const char* vSource =
		"attribute vec4 a_position;			\n\
		attribute vec2 a_texCoord0;			\n\
		varying vec2 v_texCoord0;			\n\
		uniform mat4 u_mvp;					\n\
		void main() {						\n\
		gl_Position = u_mvp * a_position;	\n\
		v_texCoord0 = a_texCoord0;			\n\
		}									\n";
	GAE_File_t* vShader = GAE_File_create("vertex shader");

	const char* fSource =
		"varying vec2 v_texCoord0;							\n\
		uniform sampler2D s_texture0;						\n\
		void main() {										\n\
		gl_FragColor = texture2D(s_texture0, v_texCoord0);	\n\
		gl_FragColor.a = 1.0;								\n\
		}													\n";
	GAE_File_t* fShader = GAE_File_create("fragment shader");

	GAE_Material_t* material = GAE_Material_create();

	float vertexData[20] = { /*Position - 12 floats */
		-1.0F, 1.0F, 0.0F,
		1.0F, 1.0F, 0.0F,
		1.0F, -1.0F, 0.0F,
		-1.0F, -1.0F, 0.0F,
		/* Tex Coords - 8 floats */
		0.0F, 0.0F,
		1.0F, 0.0F,
		1.0F, 1.0F,
		0.0F, 1.0F};

	unsigned int vertexSize = 20 * sizeof(float);
	unsigned short indexData[6] = { 0, 3, 2, 2, 1, 0 };
	unsigned int indexCount = 6U;

	GAE_VertexBuffer_t* vBuffer = GAE_VertexBuffer_create((GAE_BYTE*)vertexData, vertexSize, GAE_VERTEXBUFFER_TYPE_STATIC);
	GAE_IndexBuffer_t* iBuffer = GAE_IndexBuffer_create((GAE_BYTE*)indexData, indexCount, GAE_INDEXBUFFER_INDEX_UNSIGNED_SHORT, GAE_INDEXBUFFER_FORMAT_TRIANGLES, GAE_INDEXBUFFER_DRAW_STATIC);

	GAE_File_t* textureFile = GAE_File_create(texturePath);
	GAE_Texture_t* texture = GAE_Texture_createFromFile(textureFile);
	GAE_GL_Texture_t* glTexture = (GAE_GL_Texture_t*)texture->platform;
	glTexture->format = GAE_GL_TEXTURE_FORMAT_RGBA;
	glTexture->filter = GAE_GL_TEXTURE_FILTER_NONE;

	GAE_Texture_load(texture, GAE_FALSE);
	GAE_Material_addTexture(material, texture);
	/*GAE_Texture_delete(texture);*/

	GAE_File_setBuffer(vShader, (GAE_BYTE*)vSource, strlen(vSource), GAE_FILE_BUFFER_OWNED, 0);
	GAE_File_setBuffer(fShader, (GAE_BYTE*)fSource, strlen(fSource), GAE_FILE_BUFFER_OWNED, 0);
	material->shader = GAE_Shader_create(vShader, fShader);
	GAE_File_delete(vShader);
	GAE_File_delete(fShader);

	GAE_VertexBuffer_addFormatIdentifier(vBuffer, GAE_VERTEXBUFFER_FORMAT_POSITION_3F, 4U);
	GAE_VertexBuffer_addFormatIdentifier(vBuffer, GAE_VERTEXBUFFER_FORMAT_TEXTURE_2F, 4U);

	sprite->mesh = GAE_Mesh_create(vBuffer, iBuffer, material);
	GAE_Matrix4_setToIdentity(&sprite->transform);

	return sprite;
}

void GAE_Sprite_delete(GAE_Sprite_t* sprite) {
	GAE_Shader_delete(sprite->mesh->material->shader);
	GAE_Material_delete(sprite->mesh->material);
	GAE_VertexBuffer_delete(sprite->mesh->vBuffer);
	GAE_IndexBuffer_delete(sprite->mesh->iBuffer);
	GAE_Mesh_delete(sprite->mesh);

	free(sprite);
	sprite = 0;
}
