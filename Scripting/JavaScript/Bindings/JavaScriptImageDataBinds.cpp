#include "JavaScriptImageDataBinds.h"

#include "../../../Platform/Application.h"

using namespace GLESGAE;

const HashString GLESGAE::JS_IMAGE_DATA("ImageData");

JavaScriptImageDataBinds::JavaScriptImageDataBinds()
: JavaScriptClass<JavaScriptImageDataBinds>("ImageData")
, mData(0)
, mWidth(1.0F)
, mHeight(1.0F)
{
	addParameter("data", &jsGetData, &jsSetData);
	addParameter("width", &jsGetWidth, &jsSetWidth);
	addParameter("height", &jsGetHeight, &jsSetHeight);
}

JavaScriptImageDataBinds::JavaScriptImageDataBinds(const JavaScriptImageDataBinds& rhs)
: JavaScriptClass<JavaScriptImageDataBinds>(rhs)
, mData(rhs.mData)
, mWidth(rhs.mWidth)
, mHeight(rhs.mHeight)
{
}

JavaScriptImageDataBinds& JavaScriptImageDataBinds::operator=(const JavaScriptImageDataBinds& rhs)
{
	if (this != &rhs) {
		JavaScriptClass<JavaScriptImageDataBinds>::operator=(rhs);
		mData = rhs.mData;
		mWidth = rhs.mWidth;
		mHeight = rhs.mHeight;
	}
	
	return *this;
}

void* JavaScriptImageDataBinds::getNewInstance(size_t argc, const JSValueRef /*argv*/[])
{
	if (argc != 0) {
		Application::getInstance()->getLogger()->log("Invalid Argument Count for ImageData: " + toString(argc) + "\n", Logger::LOG_TYPE_ERROR);
		return 0;
	}
	
	JavaScriptImageDataBinds* self(new JavaScriptImageDataBinds);
	return reinterpret_cast<void*>(self);
}

JSValueRef JavaScriptImageDataBinds::jsGetData(JSContextRef /*context*/, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	JavaScriptImageDataBinds* self(reinterpret_cast<JavaScriptImageDataBinds*>(JSObjectGetPrivate(object)));
	return self->mData;
}

void JavaScriptImageDataBinds::setData(const unsigned char* data, const unsigned int width, const unsigned int height)
{
	mWidth = width;
	mHeight = height;

	const unsigned int length(width * height * 4U); // RGBA
	JSValueRef* values(new JSValueRef[length]);
	if (values == 0)
		return;
	memset(values, 0xFF, length);
	
	unsigned int index(0U);
	unsigned int fullWidth(width * 4U);
	unsigned int y(height - 1U);
	JSContextRef context(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>()->getContext());
	if (0 != data) {
		for (unsigned int row(0U); row < height; ++row) {  
			for (unsigned int x(0U); x < fullWidth; ++x) {
				values[index] = JSValueMakeNumber(context, data[x + y * fullWidth]);
				JSValueProtect(context, values[index]);
				++index;
			}
			--y;
		}
		
		// Apparently, this is needed for Impact's Fonts to work properly, as stated in appMobi's code anyway.
		JSValueRef valZero(JSValueMakeNumber(context, 0));
		for (index = 0U; index < length; index += 4) {
			unsigned int r(data[index]);
			unsigned int g(data[index + 1]);
			unsigned int b(data[index + 2]);
			if(r==0 && g==0 && b==0) values[index + 3] = valZero;
		}
		// end of hack!
	}
	
	mData = JSObjectMakeArray(context, length, reinterpret_cast<JSValueRef*>(values), 0);
	
	for (index = 0U; index < length; ++index)
		JSValueUnprotect(context, values[index]);
	
	delete [] values;
}

unsigned char* JavaScriptImageDataBinds::convertData()
{
	const unsigned int dataSize(mHeight * mWidth * 4U); // RGBA
	unsigned char* data(new unsigned char[dataSize]);
	if (0 == mData) {
		memset(data, 0xFF, dataSize);
		return data;
	}
	else {
		memset(data, 0x0, dataSize);
		
		JSContextRef context(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>()->getContext());
		JSStringRef jsString(JSValueToStringCopy(context, mData, 0));
		const unsigned int jsStringLength(JSStringGetLength(jsString));
		const JSChar* jsChar(JSStringGetCharactersPtr(jsString));
		unsigned int dataIndex(0U);
		
		for (unsigned int index(0U); index < jsStringLength; ++index) {
			if (isdigit(jsChar[index]))
				data[dataIndex] = data[dataIndex] * 10 + jsChar[index] - '0'; 
			else if(jsChar[index] == ',')
				++dataIndex;
		}
		
		JSStringRelease(jsString);
		
		return data;
	}
}

bool JavaScriptImageDataBinds::jsSetData(JSContextRef context, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception)
{
	JavaScriptImageDataBinds* self(reinterpret_cast<JavaScriptImageDataBinds*>(JSObjectGetPrivate(object)));
	JSObjectSetProperty(context, self->mData, propertyName, value, kJSPropertyAttributeNone, exception);
	return true;
}

JSValueRef JavaScriptImageDataBinds::jsGetWidth(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	JavaScriptImageDataBinds* self(reinterpret_cast<JavaScriptImageDataBinds*>(JSObjectGetPrivate(object)));
	return JSValueMakeNumber(context, self->mWidth);
}

bool JavaScriptImageDataBinds::jsSetWidth(JSContextRef /*context*/, JSObjectRef /*object*/, JSStringRef /*propertyName*/, JSValueRef /*value*/, JSValueRef* /*exception*/)
{
	return false;
}

JSValueRef JavaScriptImageDataBinds::jsGetHeight(JSContextRef context, JSObjectRef object, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	JavaScriptImageDataBinds* self(reinterpret_cast<JavaScriptImageDataBinds*>(JSObjectGetPrivate(object)));
	return JSValueMakeNumber(context, self->mHeight);
}

bool JavaScriptImageDataBinds::jsSetHeight(JSContextRef /*context*/, JSObjectRef /*object*/, JSStringRef /*propertyName*/, JSValueRef /*value*/, JSValueRef* /*exception*/)
{
	return false;
}
