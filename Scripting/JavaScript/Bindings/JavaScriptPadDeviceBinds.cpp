#include "JavaScriptPadDeviceBinds.h"

using namespace GLESGAE;

const HashString GLESGAE::JS_PAD_DEVICE("PadDevice");

JavaScriptPadDeviceBinds::JavaScriptPadDeviceBinds()
: JavaScriptClass<JavaScriptPadDeviceBinds>("PadDevice")
, mPad(0)
{
	addMethod("getButton", &jsGetButton);
	addMethod("getNumButtons", &jsGetNumButtons);
}

void* JavaScriptPadDeviceBinds::getNewInstance(size_t argc, const JSValueRef /*argv*/[])
{
	if (argc != 0) {
		Application::getInstance()->getLogger()->log("Invalid Argument Count for PadDevice: " + toString(argc) + "\n", Logger::LOG_TYPE_ERROR);
		return 0;
	}
	
	JavaScriptPadDeviceBinds* self(new JavaScriptPadDeviceBinds);
	return reinterpret_cast<void*>(self);
}

void JavaScriptPadDeviceBinds::setPad(const Controller::Id id)
{
	mPad = Application::getInstance()->getInputSystem()->getPad(id);
}

JSValueRef JavaScriptPadDeviceBinds::jsGetButton(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 1) {
		Application::getInstance()->getLogger()->log("PadDevice: invalid arguments to getButton - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		const unsigned int button(JSValueToNumber(context, arguments[0], exception));
		JavaScriptPadDeviceBinds* self(reinterpret_cast<JavaScriptPadDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mPad != 0)
			return JSValueMakeNumber(context, self->mPad->getButton(button));
		else
			return JSValueMakeNumber(context, 0);
	}
}

JSValueRef JavaScriptPadDeviceBinds::jsGetNumButtons(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	if (argumentCount != 0) {
		Application::getInstance()->getLogger()->log("PadDevice: invalid arguments to getNumButtons - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		JavaScriptPadDeviceBinds* self(reinterpret_cast<JavaScriptPadDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mPad != 0)
			return JSValueMakeNumber(context, self->mPad->getNumButtons());
		else
			return JSValueMakeNumber(context, 0);
	}
}
