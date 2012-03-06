#include "JavaScriptPointerDeviceBinds.h"

using namespace GLESGAE;

const HashString GLESGAE::JS_POINTER_DEVICE("PointerDevice");

JavaScriptPointerDeviceBinds::JavaScriptPointerDeviceBinds()
: JavaScriptClass<JavaScriptPointerDeviceBinds>("PointerDevice")
, mPointer(0)
{
	addMethod("getAxis", &jsGetAxis);
	addMethod("getButton", &jsGetButton);
	addMethod("getNumAxes", &jsGetNumAxes);
	addMethod("getNumButtons", &jsGetNumButtons);
}

void* JavaScriptPointerDeviceBinds::getNewInstance(size_t argc, const JSValueRef /*argv*/[])
{
	if (argc != 0) {
		Application::getInstance()->getLogger()->log("Invalid Argument Count for PointerDevice: " + toString(argc) + "\n", Logger::LOG_TYPE_ERROR);
		return 0;
	}
	
	JavaScriptPointerDeviceBinds* self(new JavaScriptPointerDeviceBinds);
	return reinterpret_cast<void*>(self);
}

void JavaScriptPointerDeviceBinds::setPointer(const Controller::Id pointerId)
{
	mPointer = Application::getInstance()->getInputSystem()->getPointer(pointerId);
}

JSValueRef JavaScriptPointerDeviceBinds::jsGetAxis(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 1) {
		Application::getInstance()->getLogger()->log("PointerDevice: invalid arguments to getAxis - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		const unsigned int axis(JSValueToNumber(context, arguments[0], exception));
		JavaScriptPointerDeviceBinds* self(reinterpret_cast<JavaScriptPointerDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mPointer != 0)
			return JSValueMakeNumber(context, self->mPointer->getAxis(axis));
		else
			return JSValueMakeNumber(context, 0);
	}
}

JSValueRef JavaScriptPointerDeviceBinds::jsGetButton(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 1) {
		Application::getInstance()->getLogger()->log("PointerDevice: invalid arguments to getButton - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		const unsigned int button(JSValueToNumber(context, arguments[0], exception));
		JavaScriptPointerDeviceBinds* self(reinterpret_cast<JavaScriptPointerDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mPointer != 0)
			return JSValueMakeNumber(context, self->mPointer->getButton(button));
		else
			return JSValueMakeNumber(context, 0);
	}
}

JSValueRef JavaScriptPointerDeviceBinds::jsGetNumAxes(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	if (argumentCount != 0) {
		Application::getInstance()->getLogger()->log("PointerDevice: invalid arguments to getNumAxes - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		JavaScriptPointerDeviceBinds* self(reinterpret_cast<JavaScriptPointerDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mPointer != 0)
			return JSValueMakeNumber(context, self->mPointer->getNumAxes());
		else
			return JSValueMakeNumber(context, 0);
	}
}

JSValueRef JavaScriptPointerDeviceBinds::jsGetNumButtons(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	if (argumentCount != 0) {
		Application::getInstance()->getLogger()->log("PointerDevice: invalid arguments to getNumButtons - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		JavaScriptPointerDeviceBinds* self(reinterpret_cast<JavaScriptPointerDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mPointer != 0)
			return JSValueMakeNumber(context, self->mPointer->getNumButtons());
		else
			return JSValueMakeNumber(context, 0);
	}
}
