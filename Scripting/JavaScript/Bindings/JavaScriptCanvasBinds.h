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
		
		/// Fill Rect
		static JSValueRef jsFillRect(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		/// Clear Rect
		static JSValueRef jsClearRect(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
		
		// Getters/Setters
		/// Get Width
		static JSValueRef jsGetWidth(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Width
		static bool jsSetWidth(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Height
		static JSValueRef jsGetHeight(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Height
		static bool jsSetHeight(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Fill Style
		static JSValueRef jsGetFillStyle(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Fill Style
		static bool jsSetFillStyle(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Clear Style
		static JSValueRef jsGetClearStyle(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Clear Style
		static bool jsSetClearStyle(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Global Alpha
		static JSValueRef jsGetGlobalAlpha(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Global Alpha
		static bool jsSetGlobalAlpha(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Global Composite Operation
		static JSValueRef jsGetGlobalCompositeOperation(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Global Composite Operation
		static bool jsSetGlobalCompositeOperation(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
	private:
		Resource<Mesh> makeSprite(const Resource<Texture>& texture, const float sX, const float sY, const float sW, const float sH, const float dX, const float dY, const float dW, const float dH);
		Resource<Mesh> makeQuad(const float r, const float g, const float b, const float a, const float dX, const float dY, const float dW, const float dH);
		Resource<Shader> makeShader();
		
		Resource<Texture> mTexture;
		Resource<Shader> mShader;
		Resource<Matrix4> mTransform;
		
		unsigned int mWidth;
		unsigned int mHeight;
		
		unsigned int mWindowWidth;
		unsigned int mWindowHeight;
};

}

#endif
