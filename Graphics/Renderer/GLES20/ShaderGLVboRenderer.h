#ifndef _SHADER_GL_VBO_RENDERER_H_
#define _SHADER_GL_VBO_RENDERER_H_

#if defined(GLX)
	#include "../../Context/Linux/GLee.h"
#elif defined(GLES2)
	#if defined(PANDORA) || defined(ANDROID)
		#include <GLES2/gl2.h>
	#endif
#endif

#include "../Renderer.h"

namespace GLESGAE
{
	class GLES2State;
	class Matrix4;
	class Mesh;
	class Texture;
	class VertexBuffer;
	class IndexBuffer;
	class ShaderGlVboRenderer : public Renderer
	{
		public:
			ShaderGlVboRenderer();
			~ShaderGlVboRenderer();
			
			/// Draw a Mesh using the Shader Based Pipeline
			void drawMesh(Mesh* const mesh, Matrix4* const transform);
			
		private:
			ShaderGlVboRenderer(const ShaderGlVboRenderer&);
			ShaderGlVboRenderer& operator=(const ShaderGlVboRenderer&);
			
			VertexBuffer* mLastVertexBuffer;
			IndexBuffer* mLastIndexBuffer;
			Texture* mLastTexture;
			GLES2State* mState;
	};

}

#endif

