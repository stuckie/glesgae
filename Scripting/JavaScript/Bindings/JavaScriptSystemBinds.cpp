#include "JavaScriptSystemBinds.h"

using namespace GLESGAE;

const HashString GLESGAE::JS_SYSTEM("System");

JavaScriptSystemBinds::JavaScriptSystemBinds()
: JavaScriptClass<JavaScriptSystemBinds>("System")
{
	addMethod("collectGarbage", &jsCollectGarbage);
}

void* JavaScriptSystemBinds::getNewInstance(size_t argc, const JSValueRef /*argv*/[])
{
	if (argc != 0) {
		Application::getInstance()->getLogger()->log("Invalid Argument Count for System: " + toString(argc) + "\n", Logger::LOG_TYPE_ERROR);
		return 0;
	}
	
	JavaScriptSystemBinds* self(new JavaScriptSystemBinds);
	return reinterpret_cast<void*>(self);
}

JSValueRef JavaScriptSystemBinds::jsCollectGarbage(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	if (argumentCount != 0) {
		Application::getInstance()->getLogger()->log("System: invalid arguments to collectGarbage - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeBoolean(context, false);
	}
	else {
		JavaScriptContext::collectGarbage(context);
		return JSValueMakeBoolean(context, true);
	}
}
