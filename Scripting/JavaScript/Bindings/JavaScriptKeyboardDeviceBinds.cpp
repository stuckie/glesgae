#include "JavaScriptKeyboardDeviceBinds.h"

using namespace GLESGAE;

const HashString GLESGAE::JS_KEYBOARD_DEVICE("KeyboardDevice");

JavaScriptKeyboardDeviceBinds::JavaScriptKeyboardDeviceBinds()
: JavaScriptClass<JavaScriptKeyboardDeviceBinds>("KeyboardDevice")
, mKeyboard(0)
{
	addMethod("getKey", &jsGetKey);
}

void* JavaScriptKeyboardDeviceBinds::getNewInstance(size_t argc, const JSValueRef /*argv*/[])
{
	if (argc != 0) {
		Application::getInstance()->getLogger()->log("Invalid Argument Count for KeyboardDevice: " + toString(argc) + "\n", Logger::LOG_TYPE_ERROR);
		return 0;
	}
	
	JavaScriptKeyboardDeviceBinds* self(new JavaScriptKeyboardDeviceBinds);
	return reinterpret_cast<void*>(self);
}

void JavaScriptKeyboardDeviceBinds::setKeyboard(const Controller::Id id)
{
	mKeyboard = Application::getInstance()->getInputSystem()->getKeyboard(id);
}

JSValueRef JavaScriptKeyboardDeviceBinds::jsGetKey(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 1) {
		Application::getInstance()->getLogger()->log("KeyboardDevice: invalid arguments to getAxis - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNumber(context, 0);
	}
	else {
		const unsigned int key(JSValueToNumber(context, arguments[0], exception));
		JavaScriptKeyboardDeviceBinds* self(reinterpret_cast<JavaScriptKeyboardDeviceBinds*>(JSObjectGetPrivate(thisObject)));
		if (self->mKeyboard != 0)
			return JSValueMakeNumber(context, self->mKeyboard->getKey(key));
		else
			return JSValueMakeNumber(context, 0);
	}
}
