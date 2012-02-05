#ifndef _JAVA_SCRIPT_CONTEXT_H_
#define _JAVA_SCRIPT_CONTEXT_H_

#include <vector>
#include <JavaScriptCore/JavaScript.h>
#include "../Resources/Resource.h"
#include "../Utils/HashString.h"

namespace GLESGAE
{

class BaseJavaScriptClass;
//! To keep some sense of sanity, we're effectively marking this as a static class so that there is only the one context.
//! This shouldn't matter to us too much, as we'd likely only need the one script context.
class JavaScriptContext
{
	public:
		~JavaScriptContext();
		
		/// Get an instance of the Java Script Context
		static JavaScriptContext& getInstance();

		/// Executes the specified script data in this Context, and returns any value from it.
		/// Will return NULL if there's an exception thrown.
		JSValueRef callScript(const char* data);
		
		/// Call a function.
		JSValueRef callFunction(JSObjectRef function, JSObjectRef object, size_t argc, const JSValueRef argv[]);
		
		/// Add a new Class to the Context.
		void addClass(const Resource<BaseJavaScriptClass>& scriptClass);
		
		/// Convert a JSValueRef to a String.
		std::string valueToString(JSValueRef value);
		
		/// Convert a JSValueRef to a Boolean.
		bool valueToBool(JSValueRef value);
		
		/// Convert a JSValueRef to a Number (double).
		double valueToNumber(JSValueRef value);
		
		/// Convert a JSValueRef to an ObjectRef ( effectively a void pointer )
		JSObjectRef valueToObject(JSValueRef value);
		
		/// Return reference to the Constructor of this Context.
		JSClassRef getConstructorClass() { return mConstructor; }
		
		/// Force a garbage collection.
		/// Useful for when we have some left over time.
		void collectGarbage();
		
	protected:
		/// Find a bound JavaScriptClass for this Context.
		Resource<BaseJavaScriptClass> findJavaScriptClass(const HashString classId);
		
		/// Log an exception.
		void logException(JSValueRef exception);
		
		/// Get a native class in the list of known bound classes.
		static JSValueRef getNativeClass(JSContextRef context, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception);
		
		/// Overload the constructor of the main object to find classes.
		static JSObjectRef callAsConstructor(JSContextRef context, JSObjectRef constructor, size_t argc, const JSValueRef argv[], JSValueRef* exception);

	private:
		JavaScriptContext();
		JavaScriptContext(const JavaScriptContext&);
		JavaScriptContext& operator=(const JavaScriptContext&);
		
		
		static JavaScriptContext* mInstance;
		JSGlobalContextRef mContext;
		JSClassRef mConstructor;
		std::vector<std::pair<HashString, Resource<BaseJavaScriptClass> > > mClasses;
};

}

#endif
