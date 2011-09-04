#ifndef _SHADER_BASED_CONTEXT_H_
#define _SHADER_BASED_CONTEXT_H_

#if defined(GLX)
	#include "../GLee.h"
#elif defined(GLES1)
	#if defined(PANDORA)
		#include <GLES/gl.h>
	#endif
#elif defined(GLES2)
	#if defined(PANDORA)
		#include <GLES2/gl2.h>
	#endif
#endif

#include "../Camera.h"
#include "../ShaderUniformUpdater.h"
#include "../../Resources/Resource.h"
#include <string>
#include <map>

namespace GLESGAE
{

	class Material;
	class Matrix4;
	class Mesh;
	class Shader;
	class Texture;
	class VertexBuffer;
	class IndexBuffer;
	class ShaderBasedContext
	{
		public:
			ShaderBasedContext();
			virtual ~ShaderBasedContext();
			
			/// Add a uniform updater
			void addUniformUpdater(const std::string& uniformName, const Resource<ShaderUniformUpdater>& updater);
			
			/// Clear uniform updaters
			void clearUniformUpdaters() { mUniformUpdaters.clear(); }

		protected:
			/// Draw a Mesh using the Shader Based Pipeline
			void drawMeshShaderBased(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform);

			/// Bind a shader
			void bindShader(const Resource<Shader>& shader);
			
			/// Reset all attribute location links
			void resetAttributes();
			
			/// Update all uniforms
			void updateUniforms(const Resource<Material>& material, const Resource<Matrix4>& transform);
			
			/// Update Textures
			void updateTextures(const Resource<Material>& material);
			
			/// Set the Camera
			void setShaderBasedCamera(const Resource<Camera>& camera) { mCamera = camera; }
			
			/// Enable Alpha Blending
			void enableShaderBasedBlending();
			
			/// Disable Alpha Blending
			void disableShaderBasedBlending();
			
		private:
			Resource<Shader> mCurrentShader;
			GLuint a_position;
			GLuint a_colour;
			GLuint a_normal;
			GLuint a_texCoord0;
			GLuint a_texCoord1;
			GLuint a_custom0;
			GLuint a_custom1;
			GLuint a_custom2;
			Resource<Camera> mCamera;
			Resource<VertexBuffer> mLastVertexBuffer;
			Resource<IndexBuffer> mLastIndexBuffer;
			Resource<Texture> mLastTexture;
			
			GLenum mLastTextureUnit;
			
			std::map<std::string, Resource<ShaderUniformUpdater> > mUniformUpdaters;
	};

}

#endif

