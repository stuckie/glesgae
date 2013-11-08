#include "ShaderGLVboRenderer.h"

#if defined(GLX)
	#include "../../Context/GLX/GLee.h"
#elif defined(GLES2)
	#if defined(PANDORA) || defined(ANDROID)
		#include <GLES2/gl2.h>
	#endif
#endif

#include "../../IndexBuffer.h"
#include "../../Material.h"
#include "../../Mesh.h"
#include "../../Texture.h"
#include "../../VertexBuffer.h"
#include "../../Shader.h"
#include "../../Sprite.h"
#include "../../State/GLES2/GLES2State.h"

#include <stdlib.h>

void setupAttributes(GAE_Renderer_t* renderer, GAE_VertexBuffer_t* vertexBuffer);

GAE_Renderer_t* GAE_Renderer_create(void) {
	GAE_Renderer_t* renderer = malloc(sizeof(GAE_Renderer_t));

	renderer->lastVertexBuffer = 0;
	renderer->lastIndexBuffer = 0;
	renderer->lastTexture = 0;
	renderer->state = GAE_RenderState_create();

	return renderer;
}

void GAE_Renderer_delete(GAE_Renderer_t* renderer) {
	GAE_RenderState_delete(renderer->state);
	free(renderer);
	renderer = 0;
}

GAE_Renderer_t* GAE_Renderer_drawSprite(GAE_Renderer_t* renderer, GAE_Sprite_t* sprite) {
	return GAE_Renderer_drawMesh(renderer, sprite->mesh, &sprite->transform);
}

GAE_Renderer_t* GAE_Renderer_drawMesh(GAE_Renderer_t* renderer, GAE_Mesh_t* const mesh, GAE_Matrix4_t* const transform) {
	GAE_IndexBuffer_t* const indexBuffer = mesh->iBuffer;
	GAE_VertexBuffer_t* const vertexBuffer = mesh->vBuffer;
	GAE_Material_t* const material = mesh->material;

	GAE_RenderState_bindShader(renderer->state, material->shader);
	GAE_RenderState_updateUniforms(renderer->state, material, transform);
	GAE_RenderState_updateTextures(renderer->state, material);
	
	if (renderer->lastVertexBuffer != vertexBuffer) {
		renderer->lastVertexBuffer = vertexBuffer;
		if (0 == vertexBuffer->vboId) {
			vertexBuffer->vboId = malloc(sizeof(GLuint));
			glGenBuffers(1, vertexBuffer->vboId);
			glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer->vboId);
			switch (vertexBuffer->type) {
				case GAE_VERTEXBUFFER_TYPE_STATIC:
					glBufferData(GL_ARRAY_BUFFER, vertexBuffer->size, vertexBuffer->data, GL_STATIC_DRAW);
				break;
				case GAE_VERTEXBUFFER_TYPE_STREAM:
					glBufferData(GL_ARRAY_BUFFER, vertexBuffer->size, vertexBuffer->data, GL_STREAM_DRAW);
				break;
				case GAE_VERTEXBUFFER_TYPE_DYNAMIC:
					glBufferData(GL_ARRAY_BUFFER, vertexBuffer->size, vertexBuffer->data, GL_DYNAMIC_DRAW);
				break;
			};
		}
		else {
			glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer->vboId);
			if (0 != vertexBuffer->updateData) {
				/* TODO: Assert that this buffer is either stream or dynamic.. should not be updating static buffers! */
				glBufferSubData(GL_ARRAY_BUFFER, vertexBuffer->updateData->offset, vertexBuffer->updateData->size, vertexBuffer->updateData->data);
				if (GAE_FALSE == vertexBuffer->updateData->retain) {
					free(vertexBuffer->updateData->data);
					free(vertexBuffer->updateData);
					vertexBuffer->updateData = 0;
				}
			}
		}
		
		setupAttributes(renderer, vertexBuffer);
	}

	if (renderer->lastIndexBuffer != indexBuffer) {
		renderer->lastIndexBuffer = indexBuffer;
		if (0 == indexBuffer->vboId) {
			indexBuffer->vboId = malloc(sizeof(GLuint));
			glGenBuffers(1, indexBuffer->vboId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBuffer->vboId);
			switch (indexBuffer->draw) {
				case GAE_INDEXBUFFER_DRAW_STATIC:
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->size, indexBuffer->data, GL_STATIC_DRAW);
				break;
				case GAE_INDEXBUFFER_DRAW_DYNAMIC:
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->size, indexBuffer->data, GL_DYNAMIC_DRAW);
				break;
				case GAE_INDEXBUFFER_DRAW_STREAM:
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->size, indexBuffer->data, GL_STREAM_DRAW);
				break;
			};
		}
		else {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBuffer->vboId);
			if (0 != indexBuffer->updateData) {
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->updateData->offset, indexBuffer->updateData->size, indexBuffer->updateData->data);
				if (GAE_FALSE == indexBuffer->updateData->retain) {
					free(indexBuffer->updateData->data);
					free(indexBuffer->updateData);
					indexBuffer->updateData = 0;
				}
			}
		}
	}
	
	switch (indexBuffer->type) {
		case GAE_INDEXBUFFER_INDEX_FLOAT:
			glDrawElements(GL_TRIANGLES, indexBuffer->count, GL_FLOAT, 0);
			break;
		case GAE_INDEXBUFFER_INDEX_UNSIGNED_BYTE:
			glDrawElements(GL_TRIANGLES, indexBuffer->count, GL_UNSIGNED_BYTE, 0);
			break;
		case GAE_INDEXBUFFER_INDEX_UNSIGNED_SHORT:
			glDrawElements(GL_TRIANGLES, indexBuffer->count, GL_UNSIGNED_SHORT, 0);
			break;
		default:
			break;
	};

	return renderer;
}

void setupAttributes(GAE_Renderer_t* renderer, GAE_VertexBuffer_t* vertexBuffer) {
	GAE_VertexBuffer_Format_t* const meshFormatBegin = vertexBuffer->format;
	GAE_VertexBuffer_Format_t* itr = meshFormatBegin;
	GAE_RenderState_GLES2_t* state = (GAE_RenderState_GLES2_t*)renderer->state->platform;
	unsigned int index = 0U;

	for (index = 0U; index < GAE_VERTEXBUFFER_FORMAT_SIZE; ++index) {
		itr = meshFormatBegin + index;
		switch (itr->type) {
			case GAE_VERTEXBUFFER_FORMAT_POSITION_2F:
				glVertexAttribPointer(state->a_position, 2U, GL_FLOAT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_POSITION_3F:
				glVertexAttribPointer(state->a_position, 3U, GL_FLOAT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_POSITION_4F:
				glVertexAttribPointer(state->a_position, 4U, GL_FLOAT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_POSITION_2S:
				glVertexAttribPointer(state->a_position, 2U, GL_SHORT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_POSITION_3S:
				glVertexAttribPointer(state->a_position, 3U, GL_SHORT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_POSITION_4S:
				glVertexAttribPointer(state->a_position, 4U, GL_SHORT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_POSITION_2B:
				glVertexAttribPointer(state->a_position, 2U, GL_BYTE, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_POSITION_3B:
				glVertexAttribPointer(state->a_position, 3U, GL_BYTE, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_POSITION_4B:
				glVertexAttribPointer(state->a_position, 4U, GL_BYTE, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_NORMAL_3F:
				glVertexAttribPointer(state->a_normal, 3U, GL_FLOAT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_NORMAL_3S:
				glVertexAttribPointer(state->a_normal, 3U, GL_SHORT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_NORMAL_3B:
				glVertexAttribPointer(state->a_normal, 3U, GL_BYTE, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_COLOUR_4F:
				glVertexAttribPointer(state->a_colour, 4U, GL_FLOAT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_COLOUR_3F:
				glVertexAttribPointer(state->a_colour, 3U, GL_FLOAT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_COLOUR_4S:
				glVertexAttribPointer(state->a_colour, 4U, GL_SHORT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_COLOUR_3S:
				glVertexAttribPointer(state->a_colour, 3U, GL_SHORT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_COLOUR_4UB:
				glVertexAttribPointer(state->a_colour, 4U, GL_UNSIGNED_BYTE, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_COLOUR_3UB:
				glVertexAttribPointer(state->a_colour, 3U, GL_UNSIGNED_BYTE, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			case GAE_VERTEXBUFFER_FORMAT_TEXTURE_2F:
				glVertexAttribPointer(state->a_texCoord0, 2U, GL_FLOAT, GL_FALSE, vertexBuffer->stride, (GLvoid*)&itr->offset);
				break;
			default:
				break;
		};
	}
}
