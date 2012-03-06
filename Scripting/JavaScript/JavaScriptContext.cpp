#include "JavaScriptContext.h"
#include "JavaScriptClass.h"

#include "../../Platform/Application.h"
#include "../../Utils/Logger.h"

using namespace GLESGAE;

JavaScriptContext::JavaScriptContext()
: mContext(0)
, mConstructor()
, mClasses()
, mCallbacks()
, mCallbackId(0U)
{
}

void JavaScriptContext::initialise()
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
	JSStringRef glesgaeName(JSStringCreateWithUTF8CString("glesgae"));
	JSObjectSetProperty(mContext, globalObject, glesgaeName, glesgaeObject, kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly, 0);
	JSStringRelease(glesgaeName);
}

void JavaScriptContext::update()
{
	for (std::list<std::pair<unsigned int, JavaScriptTimedFunction> >::iterator itr(mCallbacks.begin()); itr != mCallbacks.end(); ++itr) {
		if (false == itr->second.update())
			mCallbacks.erase(itr--);
	}
}

void JavaScriptContext::shutdown()
{
	for (std::vector<std::pair<HashString, Resource<BaseJavaScriptClass> > >::const_iterator itr(mClasses.begin()); itr < mClasses.end(); ++itr)
		JSClassRelease(itr->second->getClassReference());
	JSClassRelease(mConstructor);
	JSGlobalContextRelease(mContext);
	mContext = 0;
	mConstructor = 0;
	mClasses.clear();
}

JSValueRef JavaScriptContext::callScript(JSContextRef context, const char* data)
{
	if (data == 0)
		return JSValueMakeNull(context);
	JSStringRef scriptJS(JSStringCreateWithUTF8CString(data));
	JSValueRef exception(0);
	JSValueRef value(JSEvaluateScript(context, scriptJS, 0, 0, 0, &exception));
	logException(context, exception);
	JSStringRelease(scriptJS);
	
	return value;
}

JSValueRef JavaScriptContext::callFunction(JSContextRef context, JSObjectRef callback, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[])
{
	JSValueRef exception(0);
	JSValueRef result(JSObjectCallAsFunction(context, callback, thisObject, argumentCount, arguments, &exception));
	logException(context, exception);
	return result;
}

void JavaScriptContext::addClass(const Resource<BaseJavaScriptClass>& scriptClass)
{
	const HashString classId(scriptClass->getClassId());
    mClasses.push_back(std::pair<HashString, Resource<BaseJavaScriptClass> >(classId, scriptClass));
}

std::string JavaScriptContext::valueToString(JSContextRef context, JSValueRef value)
{
	JSValueRef exception(0);
	JSStringRef string(JSValueToStringCopy(context, value, &exception));
	logException(context, exception);
	return stringRefToString(string);
}

std::string JavaScriptContext::stringRefToString(JSStringRef value)
{
	const unsigned int stringSize(JSStringGetMaximumUTF8CStringSize(value));
	char* cString = new char[stringSize];
	JSStringGetUTF8CString(value, cString, stringSize);
	std::string string(cString);
	delete [] cString;
	cString = 0;
	return string;
}

bool JavaScriptContext::valueToBool(JSContextRef context, JSValueRef value)
{
	return JSValueToBoolean(context, value);
}

double JavaScriptContext::valueToNumber(JSContextRef context, JSValueRef value)
{
	JSValueRef exception(0);
	const double number(JSValueToNumber(context, value, &exception));
	logException(context, exception);
	return number;
}

JSObjectRef JavaScriptContext::valueToObject(JSContextRef context, JSValueRef value)
{
	JSValueRef exception(0);
	JSObjectRef object(JSValueToObject(context, value, &exception));
	logException(context, exception);
	return object;
}

void JavaScriptContext::collectGarbage()
{
	JSGarbageCollect(mContext);
}

Resource<BaseJavaScriptClass> JavaScriptContext::findJavaScriptClass(const HashString classId)
{
	for (std::vector<std::pair<HashString, Resource<BaseJavaScriptClass> > >::iterator itr(mClasses.begin()); itr != mClasses.end(); ++itr) {
		if (itr->first == classId)
			return itr->second;
	}
	
	Application::getInstance()->getLogger()->log("Cannot find classId: " + toString<unsigned int>(classId.getValue()) + "\n", Logger::LOG_TYPE_ERROR);
	
	return Resource<BaseJavaScriptClass>();
}

void JavaScriptContext::logException(JSContextRef context, JSValueRef exception)
{
	if (0 == exception)
		return;
	
	JSStringRef jsLinePropertyName(JSStringCreateWithUTF8CString("line"));
	JSStringRef jsFilePropertyName(JSStringCreateWithUTF8CString("sourceURL"));
	
	JSObjectRef object(JSValueToObject(context, exception, 0));
	JSValueRef line(JSObjectGetProperty(context, object, jsLinePropertyName, 0));
	JSValueRef file(JSObjectGetProperty(context, object, jsFilePropertyName, 0));
	
	const std::string exceptionString(valueToString(context, exception));
	const std::string lineString(valueToString(context, line));
	const std::string fileString(valueToString(context, file));
	
	Application::getInstance()->getLogger()->log(std::string("JavaScript: " + exceptionString + " at line: " + lineString + " in file: " + fileString + "\n"), Logger::LOG_TYPE_ERROR);
	
	JSStringRelease(jsLinePropertyName);
	JSStringRelease(jsFilePropertyName);
}

JSValueRef JavaScriptContext::getNativeClass(JSContextRef context, JSObjectRef /*object*/, JSStringRef propertyNameJS, JSValueRef* /*exception*/)
{
	const Resource<JavaScriptContext>& scriptContext(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>());
	const unsigned int stringSize(JSStringGetMaximumUTF8CStringSize(propertyNameJS));
	char* className = new char[stringSize];
	JSStringGetUTF8CString(propertyNameJS, className, stringSize);
	Resource<BaseJavaScriptClass> jsClass(scriptContext->findJavaScriptClass(HashString(className)));
	delete [] className;
	JSObjectRef object(0);
	if (jsClass != 0)
		object = JSObjectMake(context, scriptContext->getConstructorClass(), jsClass->getObjectPointer());
	
	return object ? object: JSValueMakeUndefined(context);
}

JSObjectRef JavaScriptContext::callAsConstructor(JSContextRef context, JSObjectRef constructor, size_t argc, const JSValueRef argv[], JSValueRef* /*exception*/) {
	BaseJavaScriptClass* javaClass(reinterpret_cast<BaseJavaScriptClass*>(JSObjectGetPrivate(constructor)));
	
	Resource<BaseJavaScriptClass> jsClass(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>()->findJavaScriptClass(javaClass->getClassId()));
	JSObjectRef object(JSObjectMake(context, jsClass->getClassReference(), 0));
	
	void* instance(jsClass->getNewInstance(argc, argv));
	JSObjectSetPrivate(object, instance);
	
	return object;
}

unsigned int JavaScriptContext::addCallback(const JavaScriptTimedFunction& function)
{
	mCallbacks.push_back(std::pair<unsigned int, JavaScriptTimedFunction>(mCallbackId++, function));
	return mCallbackId;
}

void JavaScriptContext::removeCallback(const unsigned int id)
{
	for (std::list<std::pair<unsigned int, JavaScriptTimedFunction> >::iterator itr(mCallbacks.begin()); itr != mCallbacks.end(); ++itr) {
		if (id == itr->first) {
			mCallbacks.erase(itr);
			return;
		}
	}
}
