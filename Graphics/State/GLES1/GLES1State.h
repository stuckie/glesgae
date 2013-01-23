#ifndef _GLES1_STATE_H_
#define _GLES1_STATE_H_

#if defined(GLX)
	#include "../../Context/Linux/GLee.h"
#elif defined(PANDORA) || defined(ANDROID)
	#if defined(GLES1)
		#include <GLES/gl.h>
	#endif
#endif

#include "../RenderState.h"

namespace GLESGAE
{
	class Matrix4;
	class Camera;
	class GLES1State : public RenderState
	{
		public:
			GLES1State();
			~GLES1State();
			
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
			
			/// Toggle Vertex Positions
			void setVertexPositionsEnabled(const bool isEnabled);
			
			/// Toggle Vertex Colours
			void setVertexColoursEnabled(const bool isEnabled);
			
			/// Toggle Vertex Normals
			void setVertexNormalsEnabled(const bool isEnabled);
			
			/// Set Blending Function
			void setBlendingFunction(const GLenum source, const GLenum destination);
			
			/// Is Texturing Enabled
			bool isTexturingEnabled() const { return mTexturing; }
			
			/// Is Alpha Blending Enabled
			bool isAlphaBlendingEnabled() const { return mAlphaBlending; }
			
			/// Is Vertex Positions Enabled
			bool isVertexPositionsEnabled() const { return mVertexPositions; }
			
			/// Is Vertex Colours Enabled
			bool isVertexColoursEnabled() const { return mVertexColours; }
			
			/// Is Vertex Normals Enabled
			bool isVertexNormalsEnabled() const { return mVertexNormals; }
			
		private:
			Resource<Camera> mCamera;
			Resource<Matrix4> mTextureMatrix;
			bool mTexturing;
			bool mAlphaBlending;
			bool mVertexPositions;
			bool mVertexColours;
			bool mVertexNormals;
	};
}

#endif
