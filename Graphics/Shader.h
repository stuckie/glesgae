#ifndef _SHADER_H_
#define _SHADER_H_

#include "../Utils/HashString.h"
#include <string>
#include <vector>

#if defined(LINUX)
	#include "Context/Linux/GLee.h"
#elif defined(PANDORA) || defined(ANDROID)
	#if defined(GLES1)
		#include <GLES/gl.h>
	#elif defined(GLES2)
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
			GLint getAttribute(const HashString attribute) const;

			/// Get Uniform Location
			GLint getUniform(const HashString uniform) const;

			/// Get Program Id
			GLuint getProgramId() const { return mShaderProgram; }
			
			/// Gain access to the attribute array
			const std::vector<std::pair<HashString, GLint> >& getAttributeArray() const { return mAttributes; }

			/// Gain access to the uniform array
			const std::vector<std::pair<HashString, GLint> >& getUniformArray() const { return mUniforms; }
			
			/// Check if this shader is ok and ready to use
			bool isOk() const { return mIsShaderOk; }

		protected:
			/// Actually load and compile the shader source
			GLuint loadShader(const std::string& shader, const GLenum type);

			/// Clear out any shader stuff we may currently have - useful for forcing a recompile of the shader
			void resetShader();

		private:
			std::vector<std::pair<HashString, GLint> > mUniforms;
			std::vector<std::pair<HashString, GLint> > mAttributes;
			GLuint mVertexShader;
			GLuint mFragmentShader;
			GLuint mShaderProgram;
			bool mIsShaderOk;
	};
}

#endif
