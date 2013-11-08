#include "Shader.h"

#if defined(GLX) || defined(GLES1) || defined(GLES2)

#include <assert.h>
#include <stdio.h>

#include "../File/File.h"
#include "../Utils/HashString.h"
#include "../Utils/Map.h"

#if defined(LINUX)
	#include "Context/GLX/GLee.h"
#elif defined(PANDORA) || defined(ANDROID)
	#if defined(GLES1)
		#include <GLES/gl.h>
	#elif defined(GLES2)
		#include <GLES2/gl2.h>
	#endif
#endif

GLuint loadShader(const char* shaderSource, const GLenum type);
void checkShaderIsLinked(GAE_Shader_t* shader);
void findShaderAttributes(GAE_Shader_t* shader);
void findShaderUniforms(GAE_Shader_t* shader);

GAE_Shader_t* GAE_Shader_create(GAE_File_t* const vFile, GAE_File_t* const fFile) {
	GAE_Shader_t* shader = malloc(sizeof(GAE_Shader_t));
	assert(shader);

	shader->attributes = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(GLint), GAE_HashString_compare);
	shader->uniforms = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(GLint), GAE_HashString_compare);
	shader->vertex = GL_INVALID_VALUE;
	shader->fragment = GL_INVALID_VALUE;
	shader->program = GL_INVALID_VALUE;

	shader->vertex = loadShader((char*)vFile->buffer, GL_VERTEX_SHADER);
	shader->fragment = loadShader((char*)fFile->buffer, GL_FRAGMENT_SHADER);
	assert(GL_INVALID_VALUE != shader->vertex);
	assert(GL_INVALID_VALUE != shader->fragment);

	shader->program = glCreateProgram();
	glAttachShader(shader->program, shader->vertex);
	glAttachShader(shader->program, shader->fragment);
	glLinkProgram(shader->program);

	checkShaderIsLinked(shader);
	assert(shader);

	if (0 != shader) {
		findShaderAttributes(shader);
		findShaderUniforms(shader);
	}

	return shader;
}

void GAE_Shader_delete(GAE_Shader_t* shader) {
	GAE_Map_delete(shader->attributes);
	GAE_Map_delete(shader->uniforms);

	if (GL_INVALID_VALUE != shader->vertex) {
		glDetachShader(shader->program, shader->vertex);
		glDeleteShader(shader->vertex);
	}
	if (GL_INVALID_VALUE != shader->fragment) {
		glDetachShader(shader->program, shader->fragment);
		glDeleteShader(shader->fragment);
	}
	if (GL_INVALID_VALUE != shader->program)
		glDeleteProgram(shader->program);

	shader->vertex = GL_INVALID_VALUE;
	shader->fragment = GL_INVALID_VALUE;
	shader->program = GL_INVALID_VALUE;

	free(shader);
	shader = 0;
}

GLint GAE_Shader_getAttribute(GAE_Shader_t* const shader, const GAE_HashString_t id) {
	GLint* value = GAE_Map_get(shader->attributes, (void*)&id);
	if (0 != value)
		return *value;
	else return GL_INVALID_VALUE;
}

GLint GAE_Shader_getUniform(GAE_Shader_t* const shader, const GAE_HashString_t id) {
	GLint* value = GAE_Map_get(shader->uniforms, (void*)&id);
	if (0 != value)
		return *value;
	else return GL_INVALID_VALUE;
}

GLuint loadShader(const char* shaderSource, const GLenum type) {
	GLuint newShader = glCreateShader(type);
	GLint isCompiled = 0;
	GLint infoLength = 0;
	char* infoLog = 0;

	glShaderSource(newShader, 1, &shaderSource, NULL);
	glCompileShader(newShader);

	glGetShaderiv(newShader, GL_COMPILE_STATUS, &isCompiled);
	if (0 == isCompiled) {
		glGetShaderiv(newShader, GL_INFO_LOG_LENGTH, &infoLength);
		if (1 < infoLength) {
			infoLog = malloc(infoLength);
			glGetShaderInfoLog(newShader, infoLength, NULL, infoLog);
			printf("%s\n", infoLog);
			/*Application::getInstance()->getLogger()->log(toString(infoLog) + "\n", Logger::LOG_TYPE_ERROR);*/
			free(infoLog);
			infoLog = 0;
		}

		glDeleteShader(newShader);
		assert(0);
		return GL_INVALID_VALUE;
	}

	return newShader;
}

void checkShaderIsLinked(GAE_Shader_t* shader) {
	GLint isLinked = 0;
	GLint infoLength = 0;
	char* infoLog = 0;

	glGetProgramiv(shader->program, GL_LINK_STATUS, &isLinked);
	if (0 == isLinked) {
		glGetProgramiv(shader->program, GL_INFO_LOG_LENGTH, &infoLength);
		if (1 < infoLength) {
			infoLog = malloc(infoLength);
			glGetShaderInfoLog(shader->program, infoLength, NULL, infoLog);
			/*Application::getInstance()->getLogger()->log(toString(infoLog) + "\n", Logger::LOG_TYPE_ERROR);*/
			free(infoLog);
			infoLog = 0;
		}

		assert(0);
		GAE_Shader_delete(shader);
	}
}

void findShaderUniforms(GAE_Shader_t* shader) {
	GLint numUniforms = 0;
	GLint maxUniformLen = 0;
	char* uniformName = 0;
	GLint index = 0;

	GLint size = 0;
	GLenum type = 0;
	GLint location = 0;

	GAE_HashString_t uniformId;

	glGetProgramiv(shader->program, GL_ACTIVE_UNIFORMS, &numUniforms);
	glGetProgramiv(shader->program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLen);
	uniformName = malloc(maxUniformLen);

	for (index = 0; index < numUniforms; ++index) {
		glGetActiveUniform(shader->program, index, maxUniformLen, NULL, &size, &type, uniformName);
		location = glGetUniformLocation(shader->program, uniformName);

		uniformId = GAE_HashString_create(uniformName);
		GAE_Map_push(shader->uniforms, &uniformId, &location);
	}

	free(uniformName);
	uniformName = 0;
}

void findShaderAttributes(GAE_Shader_t* shader) {
	GLint numAttributes = 0;
	GLint maxAttributeLen = 0;
	char* attributeName = 0;
	GLint index = 0;

	GLint size = 0;
	GLenum type = 0;
	GLint location = 0;

	GAE_HashString_t attributeId;

	glGetProgramiv(shader->program, GL_ACTIVE_ATTRIBUTES, &numAttributes);
	glGetProgramiv(shader->program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttributeLen);
	attributeName = malloc(maxAttributeLen);

	for (index = 0; index < numAttributes; ++index) {
		glGetActiveAttrib(shader->program, index, maxAttributeLen, NULL, &size, &type, attributeName);
		location = glGetAttribLocation(shader->program, attributeName);

		attributeId = GAE_HashString_create(attributeName);
		GAE_Map_push(shader->attributes, &attributeId, &location);
	}

	free(attributeName);
	attributeName = 0;
}

#endif
