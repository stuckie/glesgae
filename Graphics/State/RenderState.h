#ifndef _RENDER_STATE_H_
#define _RENDER_STATE_H_

#include "../../Resources/Resource.h"

namespace GLESGAE
{
	class Camera;
	class RenderState
	{
		public:
			virtual ~RenderState() {}
			
			/// Set the Camera
			virtual void setCamera(const Resource<Camera>& camera) = 0;
	};
}

#endif
