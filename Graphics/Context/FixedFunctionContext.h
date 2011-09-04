#ifndef _FIXED_FUNCTION_CONTEXT_H_
#define _FIXED_FUNCTION_CONTEXT_H_

#if defined(GLX)
	#include "../GLee.h"
#elif defined(GLES1)
	#if defined(PANDORA)
		#include <GLES/gl.h>
	#endif
#endif

#include "../../Resources/Resource.h"

namespace GLESGAE
{
	class Camera;
	class Matrix4;
	class Material;
	class Mesh;
	class VertexBuffer;
	class IndexBuffer;
	class Texture;
	class FixedFunctionContext
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
			FixedFunctionContext();
			virtual ~FixedFunctionContext();

			/// Enable Vertex Positions
			void enableFixedFunctionVertexPositions();

			/// Disable Vertex Positions
			void disableFixedFunctionVertexPositions();

			/// Enable Vertex Colours
			void enableFixedFunctionVertexColours();

			/// Disable Vertex Colours
			void disableFixedFunctionVertexColours();

			/// Enable Vertex Normals
			void enableFixedFunctionVertexNormals();

			/// Disable Vertex Normals
			void disableFixedFunctionVertexNormals();
			
			/// Sets the current drawing camera
			void setFixedFunctionCamera(const Resource<Camera>& camera);
			
			/// Sets the current texture matrix
			void setFixedFunctionTextureMatrix(const Resource<Matrix4>& matrix);

		protected:
			/// Draw a Mesh using the Fixed Function Pipeline
			void drawMeshFixedFunction(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform);

			/// Setup texturing - check if the requested texture unit is on and bind a texture from the material.
			void setupFixedFunctionTexturing(unsigned int* textureUnit, const Resource<Material>& material);

			/// Disable Texture Units
			void disableFixedFunctionTexturing(const unsigned int currentTextureUnit);
			
			/// Enable Alpha Blending
			void enableFixedFunctionBlending();
			
			/// Disable Alpha Blending
			void disableFixedFunctionBlending();

		private:
			bool mFixedFunctionTexUnits[8]; 			// 8 Texture Units sounds like they'd be enough to me!
			unsigned int mFixedFunctionLastTexUnit;		// Last Texture Unit we were working on, in case it's the same.
			Resource<Camera> mCamera;
			Resource<VertexBuffer> mLastVertexBuffer;
			Resource<IndexBuffer> mLastIndexBuffer;
			Resource<Texture> mLastTexture;
	};

}

#endif

