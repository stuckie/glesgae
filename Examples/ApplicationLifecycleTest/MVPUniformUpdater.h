#ifndef _MVP_UNIFORM_UPDATER_H_
#define _MVP_UNIFORM_UPDATER_H_

#include "../../Graphics/ShaderUniformUpdater.h"

class MVPUniformUpdater : public GLESGAE::ShaderUniformUpdater
{
	public:
		MVPUniformUpdater() : GLESGAE::ShaderUniformUpdater() {}
		
		void update(const GLint uniformId, GLESGAE::Camera* const camera, GLESGAE::Material* const material, GLESGAE::Matrix4* const transform);
};

#endif

