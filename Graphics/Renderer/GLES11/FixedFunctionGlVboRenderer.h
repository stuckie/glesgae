#ifndef _FIXED_FUNCTION_GL_VBO_RENDERER_H_
#define _FIXED_FUNCTION_GL_VBO_RENDERER_H_

#if defined(GLX)
	#include "../../Context/Linux/GLee.h"
#elif defined(GLES1)
	#if defined(PANDORA)
		#include <GLES/gl.h>
	#endif
#endif

#include "../Renderer.h"
#include "../../../Resources/Resource.h"

namespace GLESGAE
{
	class Camera;
	class Matrix4;
	class Material;
	class Mesh;
	class VertexBuffer;
	class IndexBuffer;
	class Texture;
	class FixedFunctionGlVboRenderer : public Renderer
	{
		/**
			The quickest way for a Fixed Function pipeline to work, is to have all data match up to a
			common format. As such, we use global state to deal with Vertex Attributes.

			This means that you really need to order your data correctly so you're doing as few state
			switches as possible when rendering - the context just renders, it doesn't organise for you.

			Additionally, dealing with multiple texture co-ordinates is a pain as we can only really deal
			with them as and when we get them, and store how many we've enabled/disabled since last time.
			Also, with a Fixed Function pipeline, each Texture must have Texture Co-ordinates, so be
			mindful of that with your data!
		**/

		public:
			FixedFunctionGlVboRenderer();
			~FixedFunctionGlVboRenderer();
			
			/// Draw a Mesh
			void drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform);
			
		protected:
			/// Setup texturing - check if the requested texture unit is on and bind a texture from the material.
			void setupTexturing(unsigned int* textureUnit, const Resource<Material>& material);
			
			/// Disable Texture Units
			void disableTexturing(const unsigned int currentTextureUnit);
			
		private:
			bool mFixedFunctionTexUnits[8]; 			// 8 Texture Units sounds like they'd be enough to me!
			unsigned int mFixedFunctionLastTexUnit;		// Last Texture Unit we were working on, in case it's the same.
			Resource<VertexBuffer> mLastVertexBuffer;
			Resource<IndexBuffer> mLastIndexBuffer;
			Resource<Texture> mLastTexture;
	};

}

#endif

