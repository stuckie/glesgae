#ifndef _JAVA_SCRIPT_PAD_DEVICE_BINDS_H_
#define _JAVA_SCRIPT_PAD_DEVICE_BINDS_H_

#include "../JavaScriptClass.h"
#include "../../../Input/Pad.h"

namespace GLESGAE
{

extern const HashString JS_PAD_DEVICE;

class JavaScriptPadDeviceBinds : public JavaScriptClass<JavaScriptPadDeviceBinds>
{
	public:
		JavaScriptPadDeviceBinds();
		
		/// Create a new object pointer for this type.
		void* getNewInstance(size_t argc, const JSValueRef argv[]);
		
		/// Get pointer to this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(this); }
		
		/// Set the pad this object is tracking.
		void setPad(const Controller::Id id);
		
		/// Get a Button value
		static JSValueRef jsGetButton(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Get amount of buttons
		static JSValueRef jsGetNumButtons(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
	
	private:
		Resource<Controller::PadController> mPad;
};

}

#endif
