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
			
			/// Get the current Camera
			virtual const Resource<Camera>& getCamera() = 0;
			
			/// Set Texturing Enabled
			virtual void setTexturingEnabled(const bool isEnabled) = 0;
			
			/// Toggle Alpha Blending
			virtual void setAlphaBlendingEnabled(const bool isEnabled) = 0;
			
			/// Is Texturing Enabled
			virtual bool isTexturingEnabled() const = 0;
			
			/// Is Alpha Blending Enabled
			virtual bool isAlphaBlendingEnabled() const = 0;
	};
}

#endif
