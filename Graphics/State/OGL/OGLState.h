#ifndef _OGL_STATE_H_
#define _OGL_STATE_H_

#if defined(GLX)
	#include "../../Context/Linux/GLee.h"
#elif defined(PANDORA) || defined(ANDROID)
	#if defined(GLES2)
		#include <GLES2/gl.h>
	#endif
#endif

#include "../RenderState.h"
#include "../../ShaderUniformUpdater.h"
#include "../../../Utils/HashString.h"

#include <string>
#include <map>

namespace GLESGAE
{
	class Material;
	class Matrix4;
	class Mesh;
	class Shader;
	class Texture;
	class OGLState : public RenderState
	{
		public:
			OGLState();
			~OGLState();
			
			/// Set the Camera.
			void setCamera(Camera* const camera);
			
			/// Sets the current texture matrix
			void setTextureMatrix(Matrix4* const matrix);
			
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
			void addUniformUpdater(const HashString uniformName, ShaderUniformUpdater* const updater);
			
			/// Clear uniform updaters
			void clearUniformUpdaters() { mUniformUpdaters.clear(); }
			
		protected:
			/// Bind a shader
			void bindShader(Shader* const shader);
			
			/// Reset all attribute location links
			void resetAttributes();
			
			/// Update all uniforms
			void updateUniforms(Material* const material, Matrix4* const transform);
			
			/// Update Textures
			void updateTextures(Material* const material);
			
		private:
			// No Copying
			OGLState(const OGLState&);
			OGLState& operator=(const OGLState&);
		
			Camera* mCamera;
			Matrix4* mTextureMatrix;
			bool mTexturing;
			bool mAlphaBlending;
			
			Shader* mCurrentShader;
			GLuint a_position;
			GLuint a_colour;
			GLuint a_normal;
			GLuint a_texCoord0;
			GLuint a_texCoord1;
			GLuint a_custom0;
			GLuint a_custom1;
			GLuint a_custom2;
			
			Texture* mLastTexture;
			GLenum mLastTextureUnit;
			
			std::map<HashString, ShaderUniformUpdater*> mUniformUpdaters;
	};
}

#endif
