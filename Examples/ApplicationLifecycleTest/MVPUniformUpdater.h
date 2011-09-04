#ifndef _MVP_UNIFORM_UPDATER_H_
#define _MVP_UNIFORM_UPDATER_H_

#include "../../Resources/Resource.h"
#include "../../Graphics/ShaderUniformUpdater.h"

class MVPUniformUpdater : public GLESGAE::ShaderUniformUpdater
{
	public:
		MVPUniformUpdater() : GLESGAE::ShaderUniformUpdater() {}
		
		void update(const GLint uniformId, const GLESGAE::Resource<GLESGAE::Camera>& camera, const GLESGAE::Resource<GLESGAE::Material>& material, const GLESGAE::Resource<GLESGAE::Matrix4>& transform);
};

#endif

