#ifndef _RENDERER_H_
#define _RENDERER_H_

namespace GLESGAE
{
	class Matrix4;
	class Mesh;
	class Renderer
	{
		public:
			virtual ~Renderer() {}
			
			/// Draw a mesh via whichever way the derived renderer performs.
			virtual void drawMesh(Mesh* const mesh, Matrix4* const transform) = 0;
	};
}

#endif
