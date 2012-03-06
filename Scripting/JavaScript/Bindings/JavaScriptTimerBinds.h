#ifndef _JAVA_SCRIPT_TIMER_BINDS_H_
#define _JAVA_SCRIPT_TIMER_BINDS_H_

#include "../JavaScriptClass.h"

namespace GLESGAE
{

extern const HashString JS_TIMER;

class JavaScriptTimerBinds : public JavaScriptClass<JavaScriptTimerBinds>
{
	public:
		JavaScriptTimerBinds();
		
		/// Create a new object pointer for this type.
		void* getNewInstance(size_t argc, const JSValueRef argv[]);
		
		/// Get pointer to this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(this); }
		
		/// Set a callback function to be triggered at a specific time.
		static JSValueRef jsSetTimeout(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Set a callback function to be repeatedly triggered at specific times.
		static JSValueRef jsSetInterval(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Clears a standard callback.
		static JSValueRef jsClearTimeout(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Clears a recurring callback.
		static JSValueRef jsClearInterval(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
};

}

#endif
