#include "Shader.h"

#ifndef GLES1

using namespace GLESGAE;

Shader::Shader()
: mUniforms()
, mAttributes()
, mVertexShader(GL_INVALID_VALUE)
, mFragmentShader(GL_INVALID_VALUE)
, mShaderProgram(GL_INVALID_VALUE)
{

}

Shader::~Shader()
{
	resetShader();
}

void Shader::createFromFile(const std::string&, const std::string&)
{
	// TODO: implement
}

void Shader::createFromSource(const std::string& vertex, const std::string& fragment)
{
	mVertexShader = loadShader(vertex, GL_VERTEX_SHADER);
	mFragmentShader = loadShader(fragment, GL_FRAGMENT_SHADER);

	if ((GL_INVALID_VALUE == mVertexShader) || (GL_INVALID_VALUE == mFragmentShader)) {
		// TODO: check that either shader has come back as GL_INVALID_VALUE and scream!
		return;
	}

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragmentShader);
	glLinkProgram(mShaderProgram);

	GLint isLinked;
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &isLinked);
	if (false == isLinked) {
		GLint infoLen(0U);

		glGetProgramiv(mShaderProgram, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			char* infoLog(new char[infoLen]);
			glGetShaderInfoLog(mShaderProgram, infoLen, NULL, infoLog);
			// TODO: something bad happened.. print the infolog and die.
			delete [] infoLog;
		}

		// TODO: Die.. something bad has happened
		resetShader();
		return;
	}

	{ // Find all Uniforms.
		GLint numUniforms;
		GLint maxUniformLen;
		glGetProgramiv(mShaderProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
		glGetProgramiv(mShaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLen);
		char* uniformName(new char[maxUniformLen]);

		for (GLint index(0); index < numUniforms; ++index) {
			GLint size;
			GLenum type;
			GLint location;

			glGetActiveUniform(mShaderProgram, index, maxUniformLen, NULL, &size, &type, uniformName);
			location = glGetUniformLocation(mShaderProgram, uniformName);

			std::pair<HashString, GLint> parameter;
			parameter.first = HashString(uniformName);
			parameter.second = location;
			mUniforms.push_back(parameter);
		}

		delete [] uniformName;
	}

	{ // Find all Attributes
		GLint numAttributes;
		GLint maxAttributeLen;
		glGetProgramiv(mShaderProgram, GL_ACTIVE_ATTRIBUTES, &numAttributes);
		glGetProgramiv(mShaderProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttributeLen);
		char* attributeName(new char[maxAttributeLen]);

		for (GLint index(0); index < numAttributes; ++index) {
			GLint size;
			GLenum type;
			GLint location;

			glGetActiveAttrib(mShaderProgram, index, maxAttributeLen, NULL, &size, &type, attributeName);
			location = glGetAttribLocation(mShaderProgram, attributeName);

			std::pair<HashString, GLint> parameter;
			parameter.first = HashString(attributeName);
			parameter.second = location;
			mAttributes.push_back(parameter);
		}

		delete [] attributeName;
	}
}

GLuint Shader::loadShader(const std::string& shader, const GLenum type)
{
	GLuint newShader(glCreateShader(type));

	const char* shaderSource(shader.c_str());
	glShaderSource(newShader, 1, &shaderSource, NULL);
	glCompileShader(newShader);

	GLint isCompiled(0);
	glGetShaderiv(newShader, GL_COMPILE_STATUS, &isCompiled);
	if (0 == isCompiled) {
		GLint infoLen(0);
		glGetShaderiv(newShader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			char* infoLog(new char[infoLen]);
			glGetShaderInfoLog(newShader, infoLen, NULL, infoLog);
			//TODO: Something bad happened.. probably want to print this!
			delete [] infoLog;
		}

		glDeleteShader(newShader);
		// TODO: catch this... this is bad
		return GL_INVALID_VALUE;
	}

	return newShader;
}

GLint Shader::getAttribute(const HashString attribute) const
{
	for (std::vector<std::pair<HashString, GLint> >::const_iterator itr(mAttributes.begin()); itr < mAttributes.end(); ++itr) {
		if (attribute == itr->first)
			return itr->second;
	}

	// TODO: catch this! obviously this is bad!
	return GL_INVALID_VALUE;
}

GLint Shader::getUniform(const HashString uniform) const
{
	for (std::vector<std::pair<HashString, GLint> >::const_iterator itr(mUniforms.begin()); itr < mUniforms.end(); ++itr) {
		if (uniform == itr->first)
			return itr->second;
	}

	// TODO: catch this! obviously this is bad!
	return GL_INVALID_VALUE;
}

void Shader::resetShader()
{
	if (GL_INVALID_VALUE != mVertexShader) {
		glDetachShader(mShaderProgram, mVertexShader);
		glDeleteShader(mVertexShader);
	}
	if (GL_INVALID_VALUE != mFragmentShader) {
		glDetachShader(mShaderProgram, mFragmentShader);
		glDeleteShader(mFragmentShader);
	}
	if (GL_INVALID_VALUE != mShaderProgram)
		glDeleteProgram(mShaderProgram);

	mUniforms.clear();
	mAttributes.clear();

	mVertexShader = GL_INVALID_VALUE;
	mFragmentShader = GL_INVALID_VALUE;
	mShaderProgram = GL_INVALID_VALUE;
}

#endif
