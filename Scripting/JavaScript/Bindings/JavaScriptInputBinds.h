#ifndef _JAVA_SCRIPT_INPUT_BINDS_H_
#define _JAVA_SCRIPT_INPUT_BINDS_H_

#include "../JavaScriptClass.h"

namespace GLESGAE
{

extern const HashString JS_INPUT;

class JavaScriptInputBinds : public JavaScriptClass<JavaScriptInputBinds>
{
	public:
		JavaScriptInputBinds();
		
		/// Create a new object pointer for this type.
		void* getNewInstance(size_t argc, const JSValueRef argv[]);
		
		/// Get pointer to this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(this); }
		
		/// Get a Pointer Device
		static JSValueRef jsGetPointer(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Get a Pad Device
		static JSValueRef jsGetPad(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Get a Joystick Device
		static JSValueRef jsGetJoystick(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Get a Keyboard Device
		static JSValueRef jsGetKeyboard(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
};

}

#endif
