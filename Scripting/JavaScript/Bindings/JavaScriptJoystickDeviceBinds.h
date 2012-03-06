#ifndef _JAVA_SCRIPT_JOYSTICK_DEVICE_BINDS_H_
#define _JAVA_SCRIPT_JOYSTICK_DEVICE_BINDS_H_

#include "../JavaScriptClass.h"
#include "../../../Input/Joystick.h"

namespace GLESGAE
{

extern const HashString JS_JOYSTICK_DEVICE;

class JavaScriptJoystickDeviceBinds : public JavaScriptClass<JavaScriptJoystickDeviceBinds>
{
	public:
		JavaScriptJoystickDeviceBinds();
		
		/// Create a new object pointer for this type.
		void* getNewInstance(size_t argc, const JSValueRef argv[]);
		
		/// Get pointer to this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(this); }
		
		/// Set the device this object is tracking.
		void setJoystick(const Controller::Id id);
		
		/// Get an Axis value
		static JSValueRef jsGetAxis(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Get a Button value
		static JSValueRef jsGetButton(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Get amount of axes
		static JSValueRef jsGetNumAxes(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Get amount of buttons
		static JSValueRef jsGetNumButtons(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
	
	private:
		Resource<Controller::JoystickController> mJoystick;
};

}

#endif
