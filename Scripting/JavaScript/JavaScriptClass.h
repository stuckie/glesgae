#ifndef _JAVA_SCRIPT_CLASS_H_
#define _JAVA_SCRIPT_CLASS_H_

#include "BaseJavaScriptClass.h"
#include "JavaScriptContext.h"
#include "../../Utils/Logger.h"

#include <cstdlib>
#include <cstring>

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
		virtual void* getNewInstance(size_t argc, const JSValueRef argv[]) = 0;
		
		/// Get a pointer to the object
		virtual void* getObjectPointer() = 0;
		
		/// Generate a new Class reference.
		JSClassRef getClassReference()
		{
			JSStaticValue* values(reinterpret_cast<JSStaticValue*>(malloc(sizeof(JSStaticValue) * (mParameters.size() + 1U))));
			memset(values, 0, sizeof(JSStaticValue) * (mParameters.size() + 1U));
			JSStaticValue* valuePtr(values);
			std::vector<char*> cStrings;
			for (std::vector<std::pair<std::string, std::pair<GetterPtr, SetterPtr> > >::iterator itr(mParameters.begin()); itr < mParameters.end(); ++itr) {
				const std::string& className(itr->first);
				std::pair<GetterPtr, SetterPtr> parameter(itr->second);
				char* cString = new char[className.size() + 1U];
				strcpy(cString, className.c_str());
				cStrings.push_back(cString);
				
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
				cStrings.push_back(cString);
				
				functionPtr->name = cString;
				functionPtr->attributes = kJSPropertyAttributeDontDelete;
				functionPtr->callAsFunction = itr->second;
				++functionPtr;
			}
			
			mClassDefinition.finalize = T_Class::garbageCollect;
			mClassDefinition.staticValues = values;
			mClassDefinition.staticFunctions = functions;
			mClassDefinition.hasProperty = hasProperty;
			JSClassRef newClass(JSClassCreate(&mClassDefinition));
			free(functions);
			free(values);
			for (std::vector<char*>::iterator itr(cStrings.begin()); itr < cStrings.end(); ++itr)
				delete [] (*itr);
			cStrings.clear();
			return newClass;
		}
		
	protected:
		/// Garbage Collection callback.
		static void garbageCollect(JSObjectRef object)
		{
			T_Class* self(reinterpret_cast<T_Class*>(JSObjectGetPrivate(object)));
			delete self;
		}
		
		/// Has Property Callback.
		static bool hasProperty(JSContextRef /*context*/, JSObjectRef object, JSStringRef propertyName)
		{
			const std::string property(JavaScriptContext::stringRefToString(propertyName));
			JavaScriptClass<T_Class>* self(reinterpret_cast<JavaScriptClass<T_Class>*>(JSObjectGetPrivate(object)));
			for (std::vector<std::pair<std::string, std::pair<GetterPtr, SetterPtr> > >::const_iterator itr(self->mParameters.begin()); itr < self->mParameters.end(); ++itr) {
				if (property == itr->first)
					return true;
			}
			
			return false;
		}
};

}

#endif
