#include "JavaScriptAudioBinds.h"
#include "../../../Platform/Application.h"

/** This is a stub just now, as we have no Audio System implemented as yet **/

using namespace GLESGAE;

const HashString GLESGAE::JS_AUDIO("Audio");

JavaScriptAudioBinds::JavaScriptAudioBinds()
: JavaScriptClass<JavaScriptAudioBinds>("Audio")
, mFile()
, mLooping(false)
, mVolume(1.0F)
, mCurrentTime(0.0F)
{
	addMethod("play", &jsPlay);
	addMethod("pause", &jsPause);
	addMethod("load", &jsLoad);
	addMethod("canPlayType", &jsCanPlayType);
	addParameter("loop", &jsGetLooping, &jsSetLooping);
	addParameter("volume", &jsGetVolume, &jsSetVolume);
	addParameter("currentTime", &jsGetCurrentTime, &jsSetCurrentTime);
}

void* JavaScriptAudioBinds::getNewInstance(size_t argc, const JSValueRef argv[])
{
	if (argc != 1) {
		Application::getInstance()->getLogger()->log("Invalid Argument Count for Audio: " + toString(argc) + "\n", Logger::LOG_TYPE_ERROR);
		return 0;
	}
	
	const Resource<JavaScriptContext>& javaContext(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>());
	Application::getInstance()->getLogger()->log("Creating Audio object for file: " + JavaScriptContext::valueToString(javaContext->getContext(), argv[0]) + "\n", Logger::LOG_TYPE_ERROR);
	
	JavaScriptAudioBinds* self(new JavaScriptAudioBinds);
	self->mFile = JavaScriptContext::valueToString(javaContext->getContext(), argv[0]);
	return reinterpret_cast<void*>(self);
}

JSValueRef JavaScriptAudioBinds::jsPlay(JSContextRef /*context*/, JSObjectRef /*function*/, JSObjectRef thisObject, size_t /*argumentCount*/, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	JavaScriptAudioBinds* self(reinterpret_cast<JavaScriptAudioBinds*>(JSObjectGetPrivate(thisObject)));
	Application::getInstance()->getLogger()->log("Playing Audio for file: " + self->mFile + "\n", Logger::LOG_TYPE_ERROR);
	return 0;
}

JSValueRef JavaScriptAudioBinds::jsPause(JSContextRef /*context*/, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t /*argumentCount*/, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	return 0;
}

JSValueRef JavaScriptAudioBinds::jsLoad(JSContextRef /*context*/, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t /*argumentCount*/, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	return 0;
}

JSValueRef JavaScriptAudioBinds::jsCanPlayType(JSContextRef /*context*/, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t /*argumentCount*/, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	return 0;
}

JSValueRef JavaScriptAudioBinds::jsGetLooping(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	JavaScriptAudioBinds* self(reinterpret_cast<JavaScriptAudioBinds*>(JSObjectGetPrivate(object)));
	return JSValueMakeBoolean(context, self->mLooping);
}

bool JavaScriptAudioBinds::jsSetLooping(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef value, JSValueRef* /*exception*/)
{
	JavaScriptAudioBinds* self(reinterpret_cast<JavaScriptAudioBinds*>(JSObjectGetPrivate(object)));
	self->mLooping = JSValueMakeBoolean(context, value);
	return true;
}

JSValueRef JavaScriptAudioBinds::jsGetVolume(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	JavaScriptAudioBinds* self(reinterpret_cast<JavaScriptAudioBinds*>(JSObjectGetPrivate(object)));
	return JSValueMakeNumber(context, self->mVolume);
}

bool JavaScriptAudioBinds::jsSetVolume(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef value, JSValueRef* /*exception*/)
{
	JavaScriptAudioBinds* self(reinterpret_cast<JavaScriptAudioBinds*>(JSObjectGetPrivate(object)));
	self->mVolume = JSValueToNumber(context, value, 0);
	return true;
}

JSValueRef JavaScriptAudioBinds::jsGetCurrentTime(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	JavaScriptAudioBinds* self(reinterpret_cast<JavaScriptAudioBinds*>(JSObjectGetPrivate(object)));
	return JSValueMakeNumber(context, self->mCurrentTime);
}

bool JavaScriptAudioBinds::jsSetCurrentTime(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef value, JSValueRef* /*exception*/)
{
	JavaScriptAudioBinds* self(reinterpret_cast<JavaScriptAudioBinds*>(JSObjectGetPrivate(object)));
	self->mCurrentTime = JSValueToNumber(context, value, 0);
	return true;
}
