#ifndef _BASE_JAVA_SCRIPT_CLASS_H_
#define _BASE_JAVA_SCRIPT_CLASS_H_

#include <JavaScriptCore/JavaScript.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include "../Utils/HashString.h"

namespace GLESGAE
{

// This is a class literally used to get a base pointer to a the templated version of JavaScriptClass,
// and provide funneled access to the template without requiring it's type.
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
		
	protected:
		BaseJavaScriptClass(const std::string& name)
		: mClassName(name)
		, mClassId(name)
		, mClassDefinition(kJSClassDefinitionEmpty)
		, mMethods()
		, mParameters()
		{
		}
		
		BaseJavaScriptClass(const BaseJavaScriptClass&);
		BaseJavaScriptClass& operator=(const BaseJavaScriptClass&);
		
		std::string mClassName;
		HashString mClassId;
		JSClassDefinition mClassDefinition;
		std::vector<std::pair<std::string, MethodPtr> > mMethods;
		std::vector<std::pair<std::string, std::pair<GetterPtr, SetterPtr> > > mParameters;
};

}

#endif
