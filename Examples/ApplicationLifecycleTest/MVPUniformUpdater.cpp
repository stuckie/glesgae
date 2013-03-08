#include "MVPUniformUpdater.h"

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

using namespace GLESGAE;

void MVPUniformUpdater::update(const GLint uniformId, Camera* const camera, Material* const, Matrix4* const transform)
{
	const Matrix4& view(camera->getViewMatrix());
	const Matrix4& projection(camera->getProjectionMatrix());

	const Matrix4 modelViewProjection(transform->getTranspose() * view * projection);

#ifndef GLES1	
	glUniformMatrix4fv(uniformId, 1U, false, modelViewProjection.getData());
#endif
}

