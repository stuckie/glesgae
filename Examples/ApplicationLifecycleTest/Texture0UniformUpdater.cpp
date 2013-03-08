#include "Texture0UniformUpdater.h"

#if defined(GLX)
	#include "../../Graphics/Context/Linux/GLee.h"
#elif defined(GLES2)
	#if defined(PANDORA)
		#include <GLES2/gl2.h>
	#endif
#endif

#include "../../Maths/Matrix4.h"
#include "../../Graphics/Camera.h"
#include "../../Graphics/Material.h"
#include "../../Graphics/Texture.h"

using namespace GLESGAE;

void Texture0UniformUpdater::update(const GLint, Camera* const, Material* const material, Matrix4* const)
{
	Texture* const texture(material->getTexture(0U));
#ifndef GLES1
	glUniform1i(texture->getId(), 0U);
#endif
}

