#ifndef _JAVA_SCRIPT_AUDIO_BINDS_H_
#define _JAVA_SCRIPT_AUDIO_BINDS_H_

#include "../JavaScriptClass.h"

namespace GLESGAE
{

extern const HashString JS_AUDIO;

class JavaScriptAudioBinds : public JavaScriptClass<JavaScriptAudioBinds>
{
	public:
		JavaScriptAudioBinds();
		
		/// Create a new object pointer for this type.
		void* getNewInstance(size_t argc, const JSValueRef argv[]);
		
		/// Get pointer to this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(this); }
		
		// JS Functions
		/// Play
		static JSValueRef jsPlay(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Pause
		static JSValueRef jsPause(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Load
		static JSValueRef jsLoad(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Can Play Type?
		static JSValueRef jsCanPlayType(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		// Getters/Setters
		/// Get Looping
		static JSValueRef jsGetLooping(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Looping
		static bool jsSetLooping(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Volume
		static JSValueRef jsGetVolume(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Volume
		static bool jsSetVolume(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Current Time
		static JSValueRef jsGetCurrentTime(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Current Time
		static bool jsSetCurrentTime(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
	private:
		std::string mFile;
		bool mLooping;
		float mVolume;
		float mCurrentTime;
};

}

#endif
