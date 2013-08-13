#ifndef _RENDER_STATE_H_
#define _RENDER_STATE_H_

namespace GLESGAE
{
	class Camera;
	class RenderState
	{
		public:
			virtual ~RenderState() {}
			
			/// Set the Camera
			virtual void setCamera(Camera* const camera) = 0;
			
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
