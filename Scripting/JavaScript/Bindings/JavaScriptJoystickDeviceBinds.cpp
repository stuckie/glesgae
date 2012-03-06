#include "JavaScriptJoystickDeviceBinds.h"

using namespace GLESGAE;

const HashString GLESGAE::JS_JOYSTICK_DEVICE("JoystickDevice");

JavaScriptJoystickDeviceBinds::JavaScriptJoystickDeviceBinds()
: JavaScriptClass<JavaScriptJoystickDeviceBinds>("JoystickDevice")
, mJoystick(0)
{
	addMethod("getAxis", &jsGetAxis);
	addMethod("getButton", &jsGetButton);
	addMethod("getNumAxes", &jsGetNumAxes);
	addMethod("getNumButtons", &jsGetNumButtons);
}

void* JavaScriptJoystickDeviceBinds::getNewInstance(size_t argc, const JSValueRef /*argv*/[])
{
	if (argc != 0) {
		Application::getInstance()->getLogger()->log("Invalid Argument Count for JoystickDevice: " + toString(argc) + "\n", Logger::LOG_TYPE_ERROR);
		return 0;
	}
	
	JavaScriptJoystickDeviceBinds* self(new JavaScriptJoystickDeviceBinds);
	return reinterpret_cast<void*>(self);
}

void JavaScriptJoystickDeviceBinds::setJoystick(const Controller::Id id)
{
	mJoystick = Application::getInstance()->getInputSystem()->getJoystick(id);
}

JSValueRef JavaScriptJoystickDeviceBinds::jsGetAxis(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 1) {
		Application::getInstance()->getLogger()->log("JoystickDevice: invalid arguments to getAxis - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		const unsigned int axis(JSValueToNumber(context, arguments[0], exception));
		JavaScriptJoystickDeviceBinds* self(reinterpret_cast<JavaScriptJoystickDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mJoystick != 0)
			return JSValueMakeNumber(context, self->mJoystick->getAxis(axis));
		else
			return JSValueMakeNumber(context, 0);
	}
}

JSValueRef JavaScriptJoystickDeviceBinds::jsGetButton(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 1) {
		Application::getInstance()->getLogger()->log("JoystickDevice: invalid arguments to getButton - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		const unsigned int button(JSValueToNumber(context, arguments[0], exception));
		JavaScriptJoystickDeviceBinds* self(reinterpret_cast<JavaScriptJoystickDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mJoystick != 0)
			return JSValueMakeNumber(context, self->mJoystick->getButton(button));
		else
			return JSValueMakeNumber(context, 0);
	}
}

JSValueRef JavaScriptJoystickDeviceBinds::jsGetNumAxes(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	if (argumentCount != 0) {
		Application::getInstance()->getLogger()->log("JoystickDevice: invalid arguments to getNumAxes - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		JavaScriptJoystickDeviceBinds* self(reinterpret_cast<JavaScriptJoystickDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mJoystick != 0)
			return JSValueMakeNumber(context, self->mJoystick->getNumAxes());
		else
			return JSValueMakeNumber(context, 0);
	}
}

JSValueRef JavaScriptJoystickDeviceBinds::jsGetNumButtons(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	if (argumentCount != 0) {
		Application::getInstance()->getLogger()->log("JoystickDevice: invalid arguments to getNumButtons - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		JavaScriptJoystickDeviceBinds* self(reinterpret_cast<JavaScriptJoystickDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mJoystick != 0)
			return JSValueMakeNumber(context, self->mJoystick->getNumButtons());
		else
			return JSValueMakeNumber(context, 0);
	}
}
