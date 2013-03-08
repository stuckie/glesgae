#ifndef _TEXTURE0_UNIFORM_UPDATER_H_
#define _TEXTURE0_UNIFORM_UPDATER_H_

#include "../../Graphics/ShaderUniformUpdater.h"

class Texture0UniformUpdater : public GLESGAE::ShaderUniformUpdater
{
	public:
		Texture0UniformUpdater() : GLESGAE::ShaderUniformUpdater() {}
		
		void update(const GLint uniformId, GLESGAE::Camera* const camera, GLESGAE::Material* const material, GLESGAE::Matrix4* const transform);
};

#endif

