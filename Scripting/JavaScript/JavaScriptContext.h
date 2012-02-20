#ifndef _JAVA_SCRIPT_CONTEXT_H_
#define _JAVA_SCRIPT_CONTEXT_H_

#include <vector>
#include <JavaScriptCore/JavaScript.h>
#include "../../Resources/Resource.h"
#include "../../Utils/HashString.h"
#include "../ScriptSystem.h"

namespace GLESGAE
{

class BaseJavaScriptClass;
class JavaScriptContext : public ScriptSystem
{
	public:
		JavaScriptContext();
		
		/// Initialise the instance.
		void initialise();
		
		/// Update this Context ( for timers )
		void update(const float delta);
		
		/// Shutdown the instance.
		void shutdown();
		
		/// Get the JSContext.
		JSContextRef getContext() { return mContext; }
		
		/// Executes the specified script data in this Context, and returns any value from it.
		/// Will return NULL if there's an exception thrown.
		static JSValueRef callScript(JSContextRef context, const char* data);
		
		/// Call a function.
		static JSValueRef callFunction(JSContextRef context, JSObjectRef callback, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[]);
		
		/// Add a new Class to the Context.
		void addClass(const Resource<BaseJavaScriptClass>& scriptClass);
		
		/// Convert a JSValueRef to a String.
		static std::string valueToString(JSContextRef context, JSValueRef value);
		
		/// Convert a JSStringRef to a String.
		static std::string stringRefToString(JSStringRef value);
		
		/// Convert a JSValueRef to a Boolean.
		static bool valueToBool(JSContextRef context, JSValueRef value);
		
		/// Convert a JSValueRef to a Number (double).
		static double valueToNumber(JSContextRef context, JSValueRef value);
		
		/// Convert a JSValueRef to an ObjectRef ( effectively a void pointer )
		static JSObjectRef valueToObject(JSContextRef context, JSValueRef value);
		
		/// Return reference to the Constructor of this Context.
		JSClassRef getConstructorClass() { return mConstructor; }
		
		/// Force a garbage collection.
		/// Useful for when we have some left over time.
		void collectGarbage();
		
	protected:
		/// Find a bound JavaScriptClass for this Context.
		Resource<BaseJavaScriptClass> findJavaScriptClass(const HashString classId);
		
		/// Log an exception.
		static void logException(JSContextRef context, JSValueRef exception);
		
		/// Get a native class in the list of known bound classes.
		static JSValueRef getNativeClass(JSContextRef context, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception);
		
		/// Overload the constructor of the main object to find classes.
		static JSObjectRef callAsConstructor(JSContextRef context, JSObjectRef constructor, size_t argc, const JSValueRef argv[], JSValueRef* exception);

	private:
		JavaScriptContext(const JavaScriptContext&);
		JavaScriptContext& operator=(const JavaScriptContext&);
		
		JSGlobalContextRef mContext;
		JSClassRef mConstructor;
		std::vector<std::pair<HashString, Resource<BaseJavaScriptClass> > > mClasses;
};

}

#endif
