#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "../../Resources/Resource.h"

namespace GLESGAE
{
	class Matrix4;
	class Mesh;
	class Renderer
	{
		public:
			virtual ~Renderer() {}
			
			/// Draw a mesh via whichever way the derived renderer performs.
			virtual void drawMesh(const Resource<Mesh>& mesh, const Resource<Matrix4>& transform) = 0;
	};
}

#endif
