#include "JavaScriptBinds.h"

#include "../../../Platform/Application.h"
#include "../../../Resources/Resource.h"
#include "../JavaScriptContext.h"

#include "JavaScriptAudioBinds.h"
#include "JavaScriptCanvasBinds.h"
#include "JavaScriptInputBinds.h"
#include "JavaScriptImageBinds.h"
#include "JavaScriptImageDataBinds.h"
#include "JavaScriptJoystickDeviceBinds.h"
#include "JavaScriptKeyboardDeviceBinds.h"
#include "JavaScriptPadDeviceBinds.h"
#include "JavaScriptPointerDeviceBinds.h"
#include "JavaScriptTimerBinds.h"

namespace GLESGAE
{

void bindGLESGAEJS()
{
	const Resource<JavaScriptContext>& context(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>());
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptAudioBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptCanvasBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptInputBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptImageBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptImageDataBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptJoystickDeviceBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptKeyboardDeviceBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptPadDeviceBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptPointerDeviceBinds));
	context->addClass(Resource<BaseJavaScriptClass>(new JavaScriptTimerBinds));
	context->callScript(context->getContext(), "Audio = glesgae.Audio");
	context->callScript(context->getContext(), "Input = new glesgae.Input");
	context->callScript(context->getContext(), "Image = glesgae.Image");
	context->callScript(context->getContext(), "ImageData = glesgae.ImageData");
	context->callScript(context->getContext(), "Timer = new glesgae.Timer();");
}

}
