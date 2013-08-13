#ifndef _SHADER_UNIFORM_UPDATER_H_
#define _SHADER_UNIFORM_UPDATER_H_

#if defined(LINUX)
	#include "Context/Linux/GLee.h"
#elif defined(PANDORA) || defined(ANDROID)
	#if defined(GLES1)
		#include <GLES/gl.h>
	#elif defined(GLES2)
		#include <GLES2/gl2.h>
	#endif
#endif

namespace GLESGAE
{
	class Camera;
	class Material;
	class Matrix4;
	class ShaderUniformUpdater
	{
		public:
			virtual ~ShaderUniformUpdater() {}
			
			/// Pure virtual to ensure you overload the update function!
			virtual void update(const GLint uniformId, Camera* const camera, Material* const material, Matrix4* const transform) = 0;
			
		protected:
			/// Protected constructor to ensure you derive from this, and don't create empty updaters.
			ShaderUniformUpdater() {}
	};
}

#endif

