#include "JavaScriptBinds.h"

#include "../../../Platform/Application.h"
#include "../../../Resources/Resource.h"
#include "../JavaScriptContext.h"

#include "JavaScriptAudioBinds.h"
#include "JavaScriptCanvasBinds.h"
#include "JavaScriptImageBinds.h"

namespace GLESGAE
{

void bindGLESGAEJS()
{
	const Resource<JavaScriptContext>& context(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>());
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptAudioBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptCanvasBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptImageBinds));
	context->callScript(context->getContext(), "Audio = glesgae.Audio");
	context->callScript(context->getContext(), "Image = glesgae.Image");
}

}