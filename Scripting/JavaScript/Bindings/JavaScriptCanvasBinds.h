#ifndef _JAVA_SCRIPT_CANVAS_BINDS_H_
#define _JAVA_SCRIPT_CANVAS_BINDS_H_

#include "../JavaScriptClass.h"

namespace GLESGAE
{

extern const HashString JS_CANVAS;

class Matrix4;
class Mesh;
class Shader;
class Texture;
class JavaScriptCanvasBinds : public JavaScriptClass<JavaScriptCanvasBinds>
{
	public:
		JavaScriptCanvasBinds();
		
		/// Create a new object pointer for this type.
		void* getNewInstance(size_t argc, const JSValueRef argv[]);
		
		/// Get pointer to this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(this); }
		
		// JS Functions
		/// Get the Context
		static JSValueRef jsGetContext(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Draw an Image
		static JSValueRef jsDrawImage(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Get Image Data from Canvas
		static JSValueRef jsGetImageData(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Put Image Data onto Canvas
		static JSValueRef jsPutImageData(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Refresh the Context
		static JSValueRef jsRefresh(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		// Getters/Setters
		/// Get Width
		static JSValueRef jsGetWidth(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Width
		static bool jsSetWidth(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Height
		static JSValueRef jsGetHeight(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Height
		static bool jsSetHeight(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
	private:
		Resource<Mesh> makeSprite(const Resource<Texture>& texture, const float sX, const float sY, const float sW, const float sH, const float dX, const float dY, const float dW, const float dH);
		Resource<Shader> makeShader();
		
		Resource<Texture> mTexture;
		Resource<Shader> mShader;
		Resource<Matrix4> mTransform;
};

}

#endif
