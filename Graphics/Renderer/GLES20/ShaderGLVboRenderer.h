#ifndef _SHADER_GL_VBO_RENDERER_H_
#define _SHADER_GL_VBO_RENDERER_H_

#if defined(GLX)
	#include "../../Context/Linux/GLee.h"
#elif defined(GLES2)
	#if defined(PANDORA)
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
			virtual ~ShaderGlVboRenderer();
			
			/// Draw a Mesh using the Shader Based Pipeline
			void drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform);
			
		private:
			Resource<VertexBuffer> mLastVertexBuffer;
			Resource<IndexBuffer> mLastIndexBuffer;
			Resource<Texture> mLastTexture;
			Resource<GLES2State> mState;
	};

}

#endif

