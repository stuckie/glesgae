#include "JavaScriptImageBinds.h"

#include "../../../Platform/Application.h"

using namespace GLESGAE;

const HashString GLESGAE::JS_IMAGE("Image");

JavaScriptImageBinds::JavaScriptImageBinds()
: JavaScriptClass<JavaScriptImageBinds>("Image")
, mTexture(0)
, mWidth(1.0F)
, mHeight(1.0F)
{
	addParameter("src", &jsGetSrc, &jsSetSrc);
	addParameter("width", &jsGetWidth, &jsSetWidth);
	addParameter("height", &jsGetHeight, &jsSetHeight);
}

void* JavaScriptImageBinds::getNewInstance(size_t argc, const JSValueRef /*argv*/[])
{
	if (argc != 0) {
		Application::getInstance()->getLogger()->log("Invalid Argument Count for Image: " + toString(argc) + "\n", Logger::LOG_TYPE_ERROR);
		return 0;
	}
	
	JavaScriptImageBinds* self(new JavaScriptImageBinds);
	return reinterpret_cast<void*>(self);
}

JSValueRef JavaScriptImageBinds::jsGetSrc(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	JavaScriptImageBinds* self(reinterpret_cast<JavaScriptImageBinds*>(JSObjectGetPrivate(object)));
	if (self->mTexture != 0) {
		JSStringRef stringRef(JSStringCreateWithUTF8CString(self->mTexture->getFile()->getFilePath().c_str()));
		JSValueRef string(JSValueMakeString(context, stringRef));
		return string;
	}
	return JSValueMakeNull(context);
}

bool JavaScriptImageBinds::jsSetSrc(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef value, JSValueRef* /*exception*/)
{
	JavaScriptImageBinds* self(reinterpret_cast<JavaScriptImageBinds*>(JSObjectGetPrivate(object)));
	if (self->mTexture == 0) {
		const std::string filePath(JavaScriptContext::valueToString(context, value));
		self->mTexture = Resource<Texture>(new Texture(Resource<File>(new File(filePath))));
		return self->mTexture->load(Texture::FILTER_NONE);
	}
	else {
		const std::string filePath(JavaScriptContext::valueToString(context, value));
		Application::getInstance()->getLogger()->log("Image already has a Texture: '" + self->mTexture->getFile()->getFilePath() + "' when trying to load: '" + filePath + "'\n", Logger::LOG_TYPE_ERROR);
	}
	return false;
}

JSValueRef JavaScriptImageBinds::jsGetWidth(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	JavaScriptImageBinds* self(reinterpret_cast<JavaScriptImageBinds*>(JSObjectGetPrivate(object)));
	return JSValueMakeNumber(context, self->mWidth);
}

bool JavaScriptImageBinds::jsSetWidth(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef value, JSValueRef* exception)
{
	JavaScriptImageBinds* self(reinterpret_cast<JavaScriptImageBinds*>(JSObjectGetPrivate(object)));
	self->mWidth = JSValueToNumber(context, value, exception);
	return true;
}

JSValueRef JavaScriptImageBinds::jsGetHeight(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	JavaScriptImageBinds* self(reinterpret_cast<JavaScriptImageBinds*>(JSObjectGetPrivate(object)));
	return JSValueMakeNumber(context, self->mHeight);
}

bool JavaScriptImageBinds::jsSetHeight(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef value, JSValueRef* exception)
{
	JavaScriptImageBinds* self(reinterpret_cast<JavaScriptImageBinds*>(JSObjectGetPrivate(object)));
	self->mWidth = JSValueToNumber(context, value, exception);
	return true;
}
