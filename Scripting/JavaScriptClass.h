#ifndef _JAVA_SCRIPT_CLASS_H_
#define _JAVA_SCRIPT_CLASS_H_

#include "BaseJavaScriptClass.h"

namespace GLESGAE
{

template <typename T_Class>
class JavaScriptClass : public BaseJavaScriptClass
{
	public:
		JavaScriptClass(const std::string& name)
		: BaseJavaScriptClass(name)
		{
		}
		
		virtual ~JavaScriptClass()
		{
		}
		
		/// Create a new instance of this class.
		/// Pure virtual and must be overloaded by deriving class.
		virtual void* getObjectPointer() = 0;
		
		/// Generate a new Class reference.
		JSClassRef getClassReference()
		{
			JSStaticValue* values(reinterpret_cast<JSStaticValue*>(malloc(sizeof(JSStaticValue) * (mParameters.size() + 1U))));
			memset(values, 0, sizeof(JSStaticValue) * (mParameters.size() + 1U));
			JSStaticValue* valuePtr(values);
			for (std::vector<std::pair<std::string, std::pair<GetterPtr, SetterPtr> > >::iterator itr(mParameters.begin()); itr < mParameters.end(); ++itr) {
				const std::string& className(itr->first);
				std::pair<GetterPtr, SetterPtr> parameter(itr->second);
				char* cString = new char[className.size() + 1U];
				strcpy(cString, className.c_str());
				
				valuePtr->name = cString;
				valuePtr->attributes = kJSPropertyAttributeDontDelete;
				valuePtr->getProperty = parameter.first;
				valuePtr->setProperty = parameter.second;
				++valuePtr;
			}
			
			JSStaticFunction* functions(reinterpret_cast<JSStaticFunction*>(malloc(sizeof(JSStaticFunction) * (mMethods.size() + 1U))));
			memset(functions, 0, sizeof(JSStaticFunction) * (mMethods.size() + 1U));
			JSStaticFunction* functionPtr(functions);
			for (std::vector<std::pair<std::string, MethodPtr> >::iterator itr(mMethods.begin()); itr < mMethods.end(); ++itr ) {
				const std::string& className(itr->first);
				char* cString = new char[className.size() + 1U];
				strcpy(cString, className.c_str());
				
				functionPtr->name = cString;
				functionPtr->attributes = kJSPropertyAttributeDontDelete;
				functionPtr->callAsFunction = itr->second;
				++functionPtr;
			}
			
			JSClassDefinition classDef(kJSClassDefinitionEmpty);
			classDef.finalize = T_Class::garbageCollect;
			classDef.staticValues = values;
			classDef.staticFunctions = functions;
			return JSClassCreate(&classDef);
		}
		
	protected:
		/// Garbage Collection callback.
		static void garbageCollect(JSObjectRef object)
		{
			T_Class* instance(reinterpret_cast<T_Class*>(JSObjectGetPrivate(object)));
			instance->T_Class::~T_Class();
		}
};

}

#endif
