#include "JavaScriptTimerBinds.h"

using namespace GLESGAE;

const HashString GLESGAE::JS_TIMER("Timer");

JavaScriptTimerBinds::JavaScriptTimerBinds()
: JavaScriptClass<JavaScriptTimerBinds>("Timer")
{
	addMethod("setTimeout", &jsSetTimeout);
	addMethod("setInterval", &jsSetInterval);
	addMethod("clearTimeout", &jsClearTimeout);
	addMethod("cleatInterval", &jsClearInterval);
}

void* JavaScriptTimerBinds::getNewInstance(size_t /*argc*/, const JSValueRef /*argv*/[])
{
	JavaScriptTimerBinds* self(new JavaScriptTimerBinds);
	return reinterpret_cast<void*>(self);
}

JSValueRef JavaScriptTimerBinds::jsSetTimeout(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 2)
		return 0;
	
	const Resource<JavaScriptContext>& javaContext(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>());
	const float callbackTime(JavaScriptContext::valueToNumber(context, arguments[1]));
	const JSObjectRef function(JSValueToObject(context, arguments[0], exception));
	return JSValueMakeNumber(context, javaContext->addCallback(JavaScriptTimedFunction(callbackTime, function, false)));
}

JSValueRef JavaScriptTimerBinds::jsSetInterval(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 2)
		return 0;
	
	const Resource<JavaScriptContext>& javaContext(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>());
	const float callbackTime(JavaScriptContext::valueToNumber(context, arguments[1]));
	const JSObjectRef function(JSValueToObject(context, arguments[0], exception));
	return JSValueMakeNumber(context, javaContext->addCallback(JavaScriptTimedFunction(callbackTime, function, true)));
}

JSValueRef JavaScriptTimerBinds::jsClearTimeout(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef arguments[], JSValueRef* /*exception*/)
{
	if (argumentCount != 1)
		return 0;
	
	const Resource<JavaScriptContext>& javaContext(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>());
	const unsigned int callbackId(JavaScriptContext::valueToNumber(context, arguments[0]));
	javaContext->removeCallback(callbackId);
	
	return 0;
}

JSValueRef JavaScriptTimerBinds::jsClearInterval(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef arguments[], JSValueRef* /*exception*/)
{
	if (argumentCount != 1)
		return 0;
	
	const Resource<JavaScriptContext>& javaContext(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>());
	const unsigned int callbackId(JavaScriptContext::valueToNumber(context, arguments[0]));
	javaContext->removeCallback(callbackId);
	
	return 0;
}
