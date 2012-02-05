#ifndef _TEST_JAVA_SCRIPT_CLASS_H_
#define _TEST_JAVA_SCRIPT_CLASS_H_

#include "./../../Scripting/JavaScriptClass.h"

class TestJavaScriptClass : public GLESGAE::JavaScriptClass<TestJavaScriptClass>
{
	public:
		TestJavaScriptClass();
		
		// Do a barrel roll!
		static JSValueRef doABarrelRoll(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Create a new object pointer for this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(new TestJavaScriptClass); }
};

#endif
