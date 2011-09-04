#ifndef _TEXTURE0_UNIFORM_UPDATER_H_
#define _TEXTURE0_UNIFORM_UPDATER_H_

#include "../../Resources/Resource.h"
#include "../../Graphics/ShaderUniformUpdater.h"

class Texture0UniformUpdater : public GLESGAE::ShaderUniformUpdater
{
	public:
		Texture0UniformUpdater() : GLESGAE::ShaderUniformUpdater() {}
		
		void update(const GLint uniformId, const GLESGAE::Resource<GLESGAE::Camera>& camera, const GLESGAE::Resource<GLESGAE::Material>& material, const GLESGAE::Resource<GLESGAE::Matrix4>& transform);
};

#endif

