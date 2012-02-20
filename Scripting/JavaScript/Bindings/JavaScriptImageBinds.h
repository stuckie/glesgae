#ifndef _JAVA_SCRIPT_IMAGE_BINDS_H_
#define _JAVA_SCRIPT_IMAGE_BINDS_H_

#include "../JavaScriptClass.h"
#include "../../../Graphics/Texture.h"

namespace GLESGAE
{

extern const HashString JS_IMAGE;

class JavaScriptImageBinds : public JavaScriptClass<JavaScriptImageBinds>
{
	public:
		JavaScriptImageBinds();
		
		/// Create a new object pointer for this type.
		void* getNewInstance(size_t argc, const JSValueRef argv[]);
		
		/// Get pointer to this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(this); }
		
		// C Functions
		/// Get the Texture
		const Resource<Texture>& getTexture() const { return mTexture; }
		
		/// Get the requested width
		float getWidth() const { return mWidth; }
		
		/// Get the requested height
		float getHeight() const { return mHeight; }
		
		// JS Functions
		
		// Getters/Setters
		/// Get Source
		static JSValueRef jsGetSrc(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Source
		static bool jsSetSrc(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Width
		static JSValueRef jsGetWidth(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Width
		static bool jsSetWidth(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Height
		static JSValueRef jsGetHeight(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Height
		static bool jsSetHeight(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
	private:
		Resource<Texture> mTexture;
		float mWidth;
		float mHeight;
};

}

#endif
