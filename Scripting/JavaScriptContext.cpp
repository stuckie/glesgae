#include "JavaScriptContext.h"
#include "JavaScriptClass.h"

#include "../Utils/Logger.h"

using namespace GLESGAE;

JavaScriptContext* JavaScriptContext::mInstance = 0;

JavaScriptContext& JavaScriptContext::getInstance()
{
	if (0 == mInstance)
		mInstance = new JavaScriptContext;
	
	return *mInstance;
}

JavaScriptContext::JavaScriptContext()
: mContext(0)
, mConstructor()
, mClasses()
{
	JSClassDefinition constructorClassDef(kJSClassDefinitionEmpty);
	constructorClassDef.callAsConstructor = callAsConstructor;
	mConstructor = JSClassCreate(&constructorClassDef);
	
	JSClassDefinition globalClassDef(kJSClassDefinitionEmpty);
	globalClassDef.getProperty = getNativeClass;
	JSClassRef globalClass(JSClassCreate(&globalClassDef));
	
	mContext = JSGlobalContextCreate(0);
	JSObjectRef globalObject(JSContextGetGlobalObject(mContext));
	JSObjectRef glesgaeObject(JSObjectMake(mContext, globalClass, 0));
	JSObjectSetProperty(mContext, globalObject, JSStringCreateWithUTF8CString("glesgae"), glesgaeObject, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly, 0);
}

JavaScriptContext::~JavaScriptContext()
{
	JSGlobalContextRelease(mContext);
}

JSValueRef JavaScriptContext::callScript(const char* data)
{
	JSStringRef scriptJS(JSStringCreateWithUTF8CString(data));
	JSValueRef exception(0);
	JSValueRef value(JSEvaluateScript(mContext, scriptJS, 0, 0, 0, &exception));
	logException(exception);
	JSStringRelease(scriptJS);
	
	return value;
}

void JavaScriptContext::addClass(const Resource<BaseJavaScriptClass>& scriptClass)
{
	const HashString classId(scriptClass->getClassId());
    mClasses.push_back(std::pair<HashString, Resource<BaseJavaScriptClass> >(classId, scriptClass));
}

std::string JavaScriptContext::valueToString(JSValueRef value)
{
	JSValueRef exception(0);
	JSStringRef string(JSValueToStringCopy(mContext, value, &exception));
	logException(exception);
	const unsigned int stringSize(JSStringGetMaximumUTF8CStringSize(string));
	char* cString = new char[stringSize];
	JSStringGetUTF8CString(string, cString, stringSize);
	return cString;
}

bool JavaScriptContext::valueToBool(JSValueRef value)
{
	return JSValueToBoolean(mContext, value);
}

double JavaScriptContext::valueToNumber(JSValueRef value)
{
	JSValueRef exception(0);
	const double number(JSValueToNumber(mContext, value, &exception));
	logException(exception);
	return number;
}

JSObjectRef JavaScriptContext::valueToObject(JSValueRef value)
{
	JSValueRef exception(0);
	JSObjectRef object(JSValueToObject(mContext, value, &exception));
	logException(exception);
	return object;
}

void JavaScriptContext::collectGarbage()
{
	JSGarbageCollect(mContext);
}

Resource<BaseJavaScriptClass> JavaScriptContext::findJavaScriptClass(const HashString classId)
{
	for (std::vector<std::pair<HashString, Resource<BaseJavaScriptClass> > >::iterator itr(mClasses.begin()); itr < mClasses.end(); ++itr) {
		if (itr->first == classId)
			return itr->second;
	}
	
	Logger::getInstance().log("Cannot find classId: " + toString<unsigned int>(classId.getValue()) + "\n", Logger::LOG_TYPE_ERROR);
	
	return 0;
}

void JavaScriptContext::logException(JSValueRef exception)
{
	if (0 == exception)
		return;
	
	JSStringRef jsLinePropertyName(JSStringCreateWithUTF8CString("line"));
	JSStringRef jsFilePropertyName(JSStringCreateWithUTF8CString("sourceURL"));
	
	JSObjectRef object(JSValueToObject(mContext, exception, 0));
	JSValueRef line(JSObjectGetProperty(mContext, object, jsLinePropertyName, 0));
	JSValueRef file(JSObjectGetProperty(mContext, object, jsFilePropertyName, 0));
	
	const std::string exceptionString(valueToString(exception));
	const std::string lineString(valueToString(line));
	const std::string fileString(valueToString(file));
	
	Logger::getInstance().log(std::string("JavaScript: " + exceptionString + " at line: " + lineString + " in file: " + lineString + "\n"), Logger::LOG_TYPE_ERROR);
	
	JSStringRelease( jsLinePropertyName );
	JSStringRelease( jsFilePropertyName );
}

JSValueRef JavaScriptContext::getNativeClass(JSContextRef context, JSObjectRef /*object*/, JSStringRef propertyNameJS, JSValueRef* /*exception*/)
{
	JavaScriptContext& scriptContext(JavaScriptContext::getInstance());
	const unsigned int stringSize(JSStringGetMaximumUTF8CStringSize(propertyNameJS));
	char* className = new char[stringSize];
	JSStringGetUTF8CString(propertyNameJS, className, stringSize);
	Resource<BaseJavaScriptClass> jsClass(scriptContext.findJavaScriptClass(HashString(className)));
	JSObjectRef object(0);
	if (jsClass != 0)
		object = JSObjectMake(context, scriptContext.getConstructorClass(), jsClass->getObjectPointer());
	
	return object ? object: JSValueMakeUndefined(context);
}

JSObjectRef JavaScriptContext::callAsConstructor(JSContextRef context, JSObjectRef constructor, size_t /*argc*/, const JSValueRef /*argv*/[], JSValueRef* /*exception*/) {
	BaseJavaScriptClass* javaClass(reinterpret_cast<BaseJavaScriptClass*>(JSObjectGetPrivate(constructor)));
	
	Resource<BaseJavaScriptClass> jsClass(JavaScriptContext::getInstance().findJavaScriptClass(javaClass->getClassId()));
	JSObjectRef object(JSObjectMake(context, jsClass->getClassReference(), 0));
	
	void* instance(jsClass->getObjectPointer());
	JSObjectSetPrivate(object, instance);
	
	return object;
}
