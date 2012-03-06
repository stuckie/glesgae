#ifndef _JAVA_SCRIPT_KEYBOARD_DEVICE_BINDS_H_
#define _JAVA_SCRIPT_KEYBOARD_DEVICE_BINDS_H_

#include "../JavaScriptClass.h"
#include "../../../Input/Keyboard.h"

namespace GLESGAE
{

extern const HashString JS_KEYBOARD_DEVICE;

class JavaScriptKeyboardDeviceBinds : public JavaScriptClass<JavaScriptKeyboardDeviceBinds>
{
	public:
		JavaScriptKeyboardDeviceBinds();
		
		/// Create a new object pointer for this type.
		void* getNewInstance(size_t argc, const JSValueRef argv[]);
		
		/// Get pointer to this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(this); }
		
		/// Set the device this object is tracking.
		void setKeyboard(const Controller::Id id);
		
		/// Get an Key value
		static JSValueRef jsGetKey(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
	
	private:
		Resource<Controller::KeyboardController> mKeyboard;
};

}

#endif
