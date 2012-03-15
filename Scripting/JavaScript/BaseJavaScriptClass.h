#ifndef _BASE_JAVA_SCRIPT_CLASS_H_
#define _BASE_JAVA_SCRIPT_CLASS_H_

#include <JavaScriptCore/JavaScript.h>
#include <list>
#include <string>
#include <vector>

#include "../../Platform/Application.h"
#include "JavaScriptContext.h"
#include "../../Utils/HashString.h"

namespace GLESGAE
{

// This is a class literally used to get a base pointer to a the templated version of JavaScriptClass, and provide funneled access to the template without requiring it's type.
class BaseJavaScriptClass
{
	public:
		typedef JSObjectGetPropertyCallback GetterPtr;
		typedef JSObjectSetPropertyCallback SetterPtr;
		typedef JSObjectCallAsFunctionCallback MethodPtr;
		
		virtual ~BaseJavaScriptClass() {}
		
		/// Get the Class Name for binding to a Context.
		const char* getClassName() const { return mClassName.c_str(); }
		
		/// Get the Class Id for finding this Class.
		HashString getClassId() const { return mClassId; }
		
		/// Pure virtual method to pull back a new instance of the derived class as a void pointer.
		/// This can only work as it's passed into the JavaScript Object, and collected via the GC's method on the templated class.
		virtual void* getNewInstance(size_t argc, const JSValueRef argv[]) = 0;
		
		/// Pointer to the Object itself.
		virtual void* getObjectPointer() = 0;
		
		/// Get the Class Reference for binding to a Context.
		/// Pure virtual to pass directly through to the templated class.
		virtual JSClassRef getClassReference() = 0;
		
		/// Add a Parameter to this Class.
		/// This requires separate Getter and Setter functions.
		void addParameter(const std::string& name, const GetterPtr getter, const SetterPtr setter)
		{
			std::pair<GetterPtr, SetterPtr> parameter(getter, setter);
			mParameters.push_back(std::pair<std::string, std::pair<GetterPtr, SetterPtr> >(name, parameter));
		}
		
		/// Add a Method to this Class.
		void addMethod(const std::string& name, const MethodPtr method)
		{
			mMethods.push_back(std::pair<std::string, MethodPtr>(name, method));
		}
		
		/// Add an Event to deal with
		void addEvent(const std::string& name)
		{
			//TODO: check this actually hasn't already been added...
			mEvents.push_back(std::pair<HashString, std::list<JSObjectRef> >(HashString(name), std::list<JSObjectRef>()));
		}
		
		/// Add an Event Listener
		static JSValueRef jsAddEventListener(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* /*exception*/)
		{
			if (argumentCount != 3)
				return JSValueMakeBoolean(context, false);
			
			BaseJavaScriptClass* self(reinterpret_cast<BaseJavaScriptClass*>(JSObjectGetPrivate(thisObject)));
			const HashString type(JavaScriptContext::valueToString(context, arguments[0]));
			for (std::vector<std::pair<HashString, std::list<JSObjectRef> > >::iterator itr(self->mEvents.begin()); itr < self->mEvents.end(); ++itr) {
				if (type == itr->first) {
					JSObjectRef functionObject(JSValueToObject(context, arguments[1], 0));
					itr->second.push_back(functionObject);
					return JSValueMakeBoolean(context, true);
				}
			}
			
			return JSValueMakeBoolean(context, false);
		}
		
		/// Trigger an Event - returns true if the type has been found, false otherwise
		bool triggerEvent(const HashString type)
		{
			for (std::vector<std::pair<HashString, std::list<JSObjectRef> > >::iterator itr(mEvents.begin()); itr < mEvents.end(); ++itr) {
				if (type == itr->first) {
					for (std::list<JSObjectRef>::const_iterator function(itr->second.begin()); function != itr->second.end(); ++function) {
						JSContextRef context(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>()->getContext());
						JavaScriptContext::callFunction(context, *function, 0, 0, 0);
					}
					return true;
				}
			}
			return false;
		}
		
		/// Remove an Event Listener
		static JSValueRef jsRemoveEventListener(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* /*exception*/)
		{
			if (argumentCount != 3)
				return JSValueMakeBoolean(context, false);
			
			BaseJavaScriptClass* self(reinterpret_cast<BaseJavaScriptClass*>(JSObjectGetPrivate(thisObject)));
			const HashString type(JavaScriptContext::valueToString(context, arguments[0]));
			for (std::vector<std::pair<HashString, std::list<JSObjectRef> > >::iterator itr(self->mEvents.begin()); itr < self->mEvents.end(); ++itr) {
				if (type == itr->first) {
					JSObjectRef functionObject(JSValueToObject(context, arguments[1], 0));
					itr->second.remove(functionObject);
					return JSValueMakeBoolean(context, true);
				}
			}
			
			return JSValueMakeBoolean(context, false);
		}
		
	protected:
		BaseJavaScriptClass(const std::string& name)
		: mClassName(name)
		, mClassId(name)
		, mClassDefinition(kJSClassDefinitionEmpty)
		, mClassRef(0)
		, mMethods()
		, mParameters()
		, mEvents()
		{
			addMethod("addEventListener", &jsAddEventListener);
			addMethod("removeEventListener", &jsRemoveEventListener);
		}
		
		BaseJavaScriptClass(const BaseJavaScriptClass& rhs)
		: mClassName(rhs.mClassName)
		, mClassId(rhs.mClassId)
		, mClassDefinition(rhs.mClassDefinition)
		, mClassRef(rhs.mClassRef)
		, mMethods(rhs.mMethods)
		, mParameters(rhs.mParameters)
		, mEvents(rhs.mEvents)
		{
		}
		
		BaseJavaScriptClass& operator=(const BaseJavaScriptClass& rhs)
		{
			if (this != &rhs) {
				mClassName = rhs.mClassName;
				mClassId = rhs.mClassId;
				mClassDefinition = rhs.mClassDefinition;
				mClassRef = rhs.mClassRef;
				mMethods = rhs.mMethods;
				mParameters = rhs.mParameters;
				mEvents = rhs.mEvents;
			}
			
			return *this;
		}
		
		std::string mClassName;
		HashString mClassId;
		JSClassDefinition mClassDefinition;
		JSClassRef mClassRef;
		std::vector<std::pair<std::string, MethodPtr> > mMethods;
		std::vector<std::pair<std::string, std::pair<GetterPtr, SetterPtr> > > mParameters;
		std::vector<std::pair<HashString, std::list<JSObjectRef> > > mEvents;
};

}

#endif
