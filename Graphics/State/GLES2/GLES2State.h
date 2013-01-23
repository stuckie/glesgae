#ifndef _GLES2_STATE_H_
#define _GLES2_STATE_H_

#if defined(GLX)
	#include "../../Context/Linux/GLee.h"
#elif defined(PANDORA) || defined(ANDROID)
	#if defined(GLES1)
		#include <GLES/gl.h>
	#elif defined(GLES2)
		#include <GLES2/gl2.h>
	#endif
#endif

#include "../RenderState.h"
#include "../../ShaderUniformUpdater.h"

#include <string>
#include <map>

namespace GLESGAE
{
	class Material;
	class Matrix4;
	class Mesh;
	class Shader;
	class ShaderUniformUpdater;
	class Texture;
	class GLES2State : public RenderState
	{
		public:
			GLES2State();
			~GLES2State();
			
			/// Set the Camera.
			void setCamera(const Resource<Camera>& camera);
			
			/// Get the Camera.
			const Resource<Camera>& getCamera() { return mCamera; }
			
			/// Sets the current texture matrix
			void setTextureMatrix(const Resource<Matrix4>& matrix);
			
			/// Get the current Texture Matrix
			const Resource<Matrix4>& getTextureMatrix() { return mTextureMatrix; }
			
			/// Toggle Texturing
			void setTexturingEnabled(const bool isEnabled);
			
			/// Toggle Alpha Blending
			void setAlphaBlendingEnabled(const bool isEnabled);
			
			/// Set Blending Function
			void setBlendingFunction(const GLenum source, const GLenum destination);
			
			/// Set Full Blending Function
			void setFullBlendingFunction(const GLenum sourceRGB, const GLenum destinationRGB
										,const GLenum sourceAlpha, const GLenum destinationAlpha);
			
			/// Is Texturing Enabled
			bool isTexturingEnabled() const { return mTexturing; }
			
			/// Is Alpha Blending Enabled
			bool isAlphaBlendingEnabled() const { return mAlphaBlending; }
			
			/// Add a uniform updater
			void addUniformUpdater(const HashString uniformName, const Resource<ShaderUniformUpdater>& updater);
			
			/// Clear uniform updaters
			void clearUniformUpdaters() { mUniformUpdaters.clear(); }
			
			/// Update all uniforms
			void updateUniforms(const Resource<Material>& material, const Resource<Matrix4>& transform);
			
			/// Update Textures
			void updateTextures(const Resource<Material>& material);
			
			/// Bind a shader
			void bindShader(const Resource<Shader>& shader);
			
			// Access to all the shader attribs
			GLuint a_position;
			GLuint a_colour;
			GLuint a_normal;
			GLuint a_texCoord0;
			GLuint a_texCoord1;
			GLuint a_custom0;
			GLuint a_custom1;
			GLuint a_custom2;
			
		protected:
			/// Reset all attribute location links
			void resetAttributes();
			
		private:
			Resource<Camera> mCamera;
			Resource<Matrix4> mTextureMatrix;
			bool mTexturing;
			bool mAlphaBlending;
			
			Resource<Shader> mCurrentShader;
			
			Resource<Texture> mLastTexture;
			GLenum mLastTextureUnit;
			
			std::map<HashString, Resource<ShaderUniformUpdater> > mUniformUpdaters;
	};
}

#endif
