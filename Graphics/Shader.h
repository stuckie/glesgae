#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <vector>

#if defined(GLX)
	#include "GLee.h"
#elif defined(GLES1)
	#if defined(PANDORA)
		#include <GLES/gl.h>
	#endif
#elif defined(GLES2)
	#if defined(PANDORA)
		#include <GLES2/gl2.h>
	#endif
#endif

namespace GLESGAE
{
	class Shader
	{
		public:
			Shader();
			~Shader();

			/// Create a shader from source
			void createFromSource(const std::string& vertex, const std::string& fragment);

			/// Create a shader from file
			void createFromFile(const std::string& vertex, const std::string& fragment);

			/// Get Attribute Location
			GLint getAttribute(const std::string& attribute) const;

			/// Get Uniform Location
			GLint getUniform(const std::string& uniform) const;

			/// Get Program Id
			GLuint getProgramId() const { return mShaderProgram; }
			
			/// Gain access to the attribute array
			const std::vector<std::pair<std::string, GLint> >& getAttributeArray() const { return mAttributes; }

			/// Gain access to the uniform array
			const std::vector<std::pair<std::string, GLint> >& getUniformArray() const { return mUniforms; }

		protected:
			/// Actually load and compile the shader source
			GLuint loadShader(const std::string& shader, const GLenum type);

			/// Clear out any shader stuff we may currently have - useful for forcing a recompile of the shader
			void resetShader();

		private:
			std::vector<std::pair<std::string, GLint> > mUniforms;
			std::vector<std::pair<std::string, GLint> > mAttributes;
			GLuint mVertexShader;
			GLuint mFragmentShader;
			GLuint mShaderProgram;
	};
}

#endif
