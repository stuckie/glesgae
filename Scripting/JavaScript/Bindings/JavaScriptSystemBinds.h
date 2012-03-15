#ifndef _JAVA_SCRIPT_SYSTEM_BINDS_H_
#define _JAVA_SCRIPT_SYSTEM_BINDS_H_

#include "../JavaScriptClass.h"

namespace GLESGAE
{

extern const HashString JS_SYSTEM;

class JavaScriptSystemBinds : public JavaScriptClass<JavaScriptSystemBinds>
{
	public:
		JavaScriptSystemBinds();
		
		/// Create a new object pointer for this type.
		void* getNewInstance(size_t argc, const JSValueRef argv[]);
		
		/// Get pointer to this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(this); }
		
		/// Force a garbage collection 
		static JSValueRef jsCollectGarbage(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
};

}

#endif
