#ifndef _JAVA_SCRIPT_IMAGE_DATA_BINDS_H_
#define _JAVA_SCRIPT_IMAGE_DATA_BINDS_H_

#include "../JavaScriptClass.h"

namespace GLESGAE
{

extern const HashString JS_IMAGE_DATA;

class JavaScriptImageDataBinds : public JavaScriptClass<JavaScriptImageDataBinds>
{
	public:
		JavaScriptImageDataBinds();
		JavaScriptImageDataBinds(const JavaScriptImageDataBinds& rhs);
		JavaScriptImageDataBinds& operator=(const JavaScriptImageDataBinds& rhs);
		~JavaScriptImageDataBinds();
		
		/// Create a new object pointer for this type.
		void* getNewInstance(size_t argc, const JSValueRef argv[]);
		
		/// Get pointer to this type.
		void* getObjectPointer() { return reinterpret_cast<void*>(this); }
		
		// C Functions
		/// Set the Data
		void setData(const unsigned char* data, const unsigned int width, const unsigned int height);
		
		/// Converts the data back to loadable data.
		/// Delete this pointer after use.
		unsigned char* convertData();
		
		/// Returns the size of the data returned by convertData.
		unsigned int getSize() { return static_cast<unsigned int>(mWidth * mHeight * 4U); }
		
		/// Get the requested width
		float getWidth() const { return mWidth; }
		
		/// Get the requested height
		float getHeight() const { return mHeight; }
		
		// Getters/Setters
		/// Get Data
		static JSValueRef jsGetData(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Data
		static bool jsSetData(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Width
		static JSValueRef jsGetWidth(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Width
		static bool jsSetWidth(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
		/// Get Height
		static JSValueRef jsGetHeight(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
		
		/// Set Height
		static bool jsSetHeight(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);
		
	private:
		JSObjectRef mData;
		float mWidth;
		float mHeight;
};

}

#endif
