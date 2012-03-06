#include "JavaScriptInputBinds.h"
#include "JavaScriptPointerDeviceBinds.h"
#include "JavaScriptPadDeviceBinds.h"
#include "JavaScriptJoystickDeviceBinds.h"
#include "JavaScriptKeyboardDeviceBinds.h"

using namespace GLESGAE;

const HashString JS_INPUT("Input");

JavaScriptInputBinds::JavaScriptInputBinds()
: JavaScriptClass<JavaScriptInputBinds>("Input")
{
	addMethod("getPointer", &jsGetPointer);
	addMethod("getPad", &jsGetPad);
	addMethod("getJoystick", &jsGetJoystick);
	addMethod("getKeyboard", &jsGetKeyboard);
}

void* JavaScriptInputBinds::getNewInstance(size_t argc, const JSValueRef /*argv*/[])
{
	if (argc != 0) {
		Application::getInstance()->getLogger()->log("Invalid Argument Count for Input: " + toString(argc) + "\n", Logger::LOG_TYPE_ERROR);
		return 0;
	}
	
	JavaScriptInputBinds* self(new JavaScriptInputBinds);
	return reinterpret_cast<void*>(self);
}

JSValueRef JavaScriptInputBinds::jsGetPointer(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 1) {
		Application::getInstance()->getLogger()->log("Input: invalid arguments to GetPointer - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNull(context);
	}
	else {
		const unsigned int index(JSValueToNumber(context, arguments[0], exception));
		JSStringRef scriptJS(JSStringCreateWithUTF8CString("return new glesgae.PointerDevice()"));
		JSObjectRef function(JSObjectMakeFunction(context, 0, 0, 0, scriptJS, 0, 1, 0));
		JSValueRef result(JSObjectCallAsFunction(context, function, 0, 0, 0, 0));
		JSStringRelease(scriptJS);
		JavaScriptPointerDeviceBinds* device(reinterpret_cast<JavaScriptPointerDeviceBinds*>(JSObjectGetPrivate(JSValueToObject(context, result, 0))));
		if (device->getClassId() != JS_POINTER_DEVICE) {
			Application::getInstance()->getLogger()->log("Could not create a Pointer Device - " + toString(device->getClassName()) + "\n", Logger::LOG_TYPE_ERROR);
			return JSValueMakeNull(context);
		}
		device->setPointer(index);
		return result;
	}
}

JSValueRef JavaScriptInputBinds::jsGetPad(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 1) {
		Application::getInstance()->getLogger()->log("Input: invalid arguments to GetPad - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNull(context);
	}
	else {
		const unsigned int index(JSValueToNumber(context, arguments[0], exception));
		JSStringRef scriptJS(JSStringCreateWithUTF8CString("return new glesgae.PadDevice()"));
		JSObjectRef function(JSObjectMakeFunction(context, 0, 0, 0, scriptJS, 0, 1, 0));
		JSValueRef result(JSObjectCallAsFunction(context, function, 0, 0, 0, 0));
		JSStringRelease(scriptJS);
		JavaScriptPadDeviceBinds* device(reinterpret_cast<JavaScriptPadDeviceBinds*>(JSObjectGetPrivate(JSValueToObject(context, result, 0))));
		if (device->getClassId() != JS_PAD_DEVICE) {
			Application::getInstance()->getLogger()->log("Could not create a Pad Device - " + toString(device->getClassName()) + "\n", Logger::LOG_TYPE_ERROR);
			return JSValueMakeNull(context);
		}
		device->setPad(index);
		return result;
	}
}

JSValueRef JavaScriptInputBinds::jsGetJoystick(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 1) {
		Application::getInstance()->getLogger()->log("Input: invalid arguments to GetJoystick - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNull(context);
	}
	else {
		const unsigned int index(JSValueToNumber(context, arguments[0], exception));
		JSStringRef scriptJS(JSStringCreateWithUTF8CString("return new glesgae.JoystickDevice()"));
		JSObjectRef function(JSObjectMakeFunction(context, 0, 0, 0, scriptJS, 0, 1, 0));
		JSValueRef result(JSObjectCallAsFunction(context, function, 0, 0, 0, 0));
		JSStringRelease(scriptJS);
		JavaScriptJoystickDeviceBinds* device(reinterpret_cast<JavaScriptJoystickDeviceBinds*>(JSObjectGetPrivate(JSValueToObject(context, result, 0))));
		if (device->getClassId() != JS_JOYSTICK_DEVICE) {
			Application::getInstance()->getLogger()->log("Could not create a Joystick Device - " + toString(device->getClassName()) + "\n", Logger::LOG_TYPE_ERROR);
			return JSValueMakeNull(context);
		}
		device->setJoystick(index);
		return result;
	}
}

JSValueRef JavaScriptInputBinds::jsGetKeyboard(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	if (argumentCount != 1) {
		Application::getInstance()->getLogger()->log("Input: invalid arguments to GetPointer - " + toString(argumentCount) + "\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNull(context);
	}
	else {
		const unsigned int index(JSValueToNumber(context, arguments[0], exception));
		JSStringRef scriptJS(JSStringCreateWithUTF8CString("return new glesgae.KeyboardDevice()"));
		JSObjectRef function(JSObjectMakeFunction(context, 0, 0, 0, scriptJS, 0, 1, 0));
		JSValueRef result(JSObjectCallAsFunction(context, function, 0, 0, 0, 0));
		JSStringRelease(scriptJS);
		JavaScriptKeyboardDeviceBinds* device(reinterpret_cast<JavaScriptKeyboardDeviceBinds*>(JSObjectGetPrivate(JSValueToObject(context, result, 0))));
		if (device->getClassId() != JS_KEYBOARD_DEVICE) {
			Application::getInstance()->getLogger()->log("Could not create a Keyboard Device - " + toString(device->getClassName()) + "\n", Logger::LOG_TYPE_ERROR);
			return JSValueMakeNull(context);
		}
		device->setKeyboard(index);
		return result;
	}
}
