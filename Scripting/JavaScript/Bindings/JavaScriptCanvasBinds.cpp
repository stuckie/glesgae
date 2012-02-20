#include "JavaScriptCanvasBinds.h"

#include "../../../Platform/Application.h"
#include "../../../Maths/Matrix4.h"
#include "../../../Graphics/Mesh.h"
#include "../../../Graphics/Shader.h"
#include "../../../Graphics/Texture.h"
#include "../../../Graphics/VertexBuffer.h"
#include "../../../Graphics/IndexBuffer.h"
#include "../../../Graphics/Material.h"
#include "JavaScriptImageBinds.h"

using namespace GLESGAE;

const HashString GLESGAE::JS_CANVAS("Canvas");

JavaScriptCanvasBinds::JavaScriptCanvasBinds()
: JavaScriptClass<JavaScriptCanvasBinds>("Canvas")
, mTexture()
, mShader(makeShader())
, mTransform(new Matrix4)
{
	mTransform->setToIdentity();
	addMethod("getContext", &jsGetContext);
	addMethod("drawImage", &jsDrawImage);
	addMethod("getImageData", &jsGetImageData);
	addMethod("putImageData", &jsPutImageData);
	addMethod("refresh", &jsRefresh);
	addParameter("width", &jsGetWidth, &jsSetWidth);
	addParameter("height", &jsGetHeight, &jsSetHeight);
}

void* JavaScriptCanvasBinds::getNewInstance(size_t argc, const JSValueRef /*argv*/[])
{
	if (argc != 0) {
		Application::getInstance()->getLogger()->log("Invalid Argument Count for Canvas: " + toString(argc) + "\n", Logger::LOG_TYPE_ERROR);
		return 0;
	}
	
	JavaScriptCanvasBinds* self(new JavaScriptCanvasBinds);
	return reinterpret_cast<void*>(self);
}

JSValueRef JavaScriptCanvasBinds::jsGetContext(JSContextRef /*context*/, JSObjectRef /*function*/, JSObjectRef thisObject, size_t /*argumentCount*/, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	return reinterpret_cast<JSValueRef>(thisObject);
}

JSValueRef JavaScriptCanvasBinds::jsDrawImage(JSContextRef context, JSObjectRef /*function*/, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* /*exception*/)
{
	if ((argumentCount != 3) && (argumentCount != 5) && (argumentCount != 9)) {
		Application::getInstance()->getLogger()->log("Invalid arguments to Canvas:drawImage.\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeBoolean(context, false);
	}
	else {
		const JavaScriptImageBinds* image(reinterpret_cast<const JavaScriptImageBinds*>(JSObjectGetPrivate(JSValueToObject(context, arguments[0], 0))));
		if (image->getClassId() != JS_IMAGE) {
			Application::getInstance()->getLogger()->log("First Parameter Not an Image to Canvas:drawImage - " + toString(image->getClassName()) + "\n", Logger::LOG_TYPE_ERROR);
			return JSValueMakeBoolean(context, false);
		}
		
		float dX, dY, dW, dH, sX, sY, sW, sH;
		if (argumentCount == 3) {
			sX = 0.0F;
			sY = 0.0F;
			sW = image->getTexture()->getWidth();
			sH = image->getTexture()->getHeight();
			dX = JSValueToNumber(context, arguments[1], 0);
			dY = JSValueToNumber(context, arguments[2], 0);
			dW = image->getTexture()->getWidth();
			dH = image->getTexture()->getHeight();
		} else if(argumentCount == 5) {
			sX = 0.0F;
			sY = 0.0F;
			sW = image->getTexture()->getWidth();
			sH = image->getTexture()->getHeight();
			dX = JSValueToNumber(context, arguments[1], 0);
			dY = JSValueToNumber(context, arguments[2], 0);
			dW = JSValueToNumber(context, arguments[3], 0);
			dH = JSValueToNumber(context, arguments[4], 0);
		} else {
			sX = JSValueToNumber(context, arguments[1], 0);
			sY = JSValueToNumber(context, arguments[2], 0);
			sW = JSValueToNumber(context, arguments[3], 0);
			sH = JSValueToNumber(context, arguments[4], 0);
			dX = JSValueToNumber(context, arguments[5], 0);
			dY = JSValueToNumber(context, arguments[6], 0);
			dW = JSValueToNumber(context, arguments[7], 0);
			dH = JSValueToNumber(context, arguments[8], 0);
		}
		
		JavaScriptCanvasBinds* self(reinterpret_cast<JavaScriptCanvasBinds*>(JSObjectGetPrivate(thisObject)));
		const Resource<Mesh> mesh(self->makeSprite(image->getTexture(), sX, sY, sW, sH, dX, dY, dW, dH));
		Application::getInstance()->getGraphicsSystem()->getCurrentContext()->drawMesh(mesh, self->mTransform);
		return JSValueMakeBoolean(context, true);
	}
}

JSValueRef JavaScriptCanvasBinds::jsGetImageData(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef arguments[], JSValueRef* /*exception*/)
{
	if (argumentCount != 4) {
		Application::getInstance()->getLogger()->log("Invalid arguments Canvas:getImageData.\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNull(context);
	}
	else {
		const float sX(JSValueToNumber(context, arguments[0], 0));
		const float sY(JSValueToNumber(context, arguments[1], 0));
		const float sW(JSValueToNumber(context, arguments[2], 0));
		const float sH(JSValueToNumber(context, arguments[3], 0));
		
		// Need to tell the Context to refresh just now, so we're grabbing exact pixels.
		Application::getInstance()->getGraphicsSystem()->getCurrentContext()->refresh();
		
		// We return RGBA data, so that's width * height * 4
		const unsigned int dataSize(sW * sH * 4);
		unsigned char* data(new unsigned char[dataSize]);
		memset(data, 0x0, dataSize);
		// Technically this is naughty, and should be hidden in the context...
		glReadPixels(sX, sY, sW, sH, GL_RGBA, GL_UNSIGNED_BYTE, data);
		
		/*JSStringRef scriptJS(JSStringCreateWithUTF8CString("return new glesgae.ImageData()"));
		JSObjectRef function(JSObjectMakeFunction(context, 0, 0, 0, scriptJS, 0, 1, 0));
		JSValueRef result(JSObjectCallAsFunction(context, function, 0, 0, 0, 0));
		JavaScriptImageDataBinds* imageData(JSObjectGetPrivate(JSValueToObject(context, result, 0)));
		imageData->setData(sW, sH, data);
		JSStringRelease(scriptJS);
		return result;*/
		return 0;
	}
}

JSValueRef JavaScriptCanvasBinds::jsPutImageData(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	if ((argumentCount != 3) || (argumentCount != 7)) {
		Application::getInstance()->getLogger()->log("Invalid arguments Canvas:putImageData.\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeNull(context);
	}
	else {
		// Create an image based on the ImageData pointer
		// Draw it as a normal sprite
		// Let it die.
		return 0;
	}
}

JSValueRef JavaScriptCanvasBinds::jsRefresh(JSContextRef context, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t argumentCount, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	if (argumentCount != 0) {
		Application::getInstance()->getLogger()->log("Invalid arguments Canvas:refresh.\n", Logger::LOG_TYPE_ERROR);
		return JSValueMakeBoolean(context, false);
	}
	else {
		Application::getInstance()->getGraphicsSystem()->getCurrentContext()->refresh();
		return JSValueMakeBoolean(context, true);
	}
}

JSValueRef JavaScriptCanvasBinds::jsGetWidth(JSContextRef context, JSObjectRef /*object*/, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	return JSValueMakeNumber(context, Application::getInstance()->getGraphicsSystem()->getCurrentWindow()->getWidth());
}

bool JavaScriptCanvasBinds::jsSetWidth(JSContextRef /*context*/, JSObjectRef /*object*/, JSStringRef /*propertyName*/, JSValueRef /*value*/, JSValueRef* /*exception*/)
{
	return false;
}

JSValueRef JavaScriptCanvasBinds::jsGetHeight(JSContextRef context, JSObjectRef /*object*/, JSStringRef /*propertyName*/, JSValueRef* /*exception*/)
{
	return JSValueMakeNumber(context, Application::getInstance()->getGraphicsSystem()->getCurrentWindow()->getHeight());
}

bool JavaScriptCanvasBinds::jsSetHeight(JSContextRef /*context*/, JSObjectRef /*object*/, JSStringRef /*propertyName*/, JSValueRef /*value*/, JSValueRef* /*exception*/)
{
	return false;
}

Resource<Mesh> JavaScriptCanvasBinds::makeSprite(const Resource<Texture>& texture, const float sX, const float sY, const float sW, const float sH, const float dX, const float dY, const float dW, const float dH)
{
	float vertexData[16] = {// Position - 8 floats
					dX, 		dY,
					dX + dW, 	dY,
					dX, 		dY + dH,
					dX + dW, 	dY + dH,
					// Tex Coords - 8 floats
					sX / texture->getWidth()		, (sY + sH) / texture->getHeight(),
					(sX + sW) / texture->getWidth()	, (sY + sH) / texture->getHeight(),
					sX / texture->getWidth()		, sY / texture->getHeight(),
					(sX + sW) / texture->getWidth()	, sY / texture->getHeight()};
	
	unsigned int vertexSize = 16 * sizeof(float);
	
	unsigned char indexData[6] = { 0, 1, 2, 1, 2, 3 };
	unsigned int indexSize = 6 * sizeof(unsigned char);
	
	Resource<VertexBuffer> newVertexBuffer(new VertexBuffer(reinterpret_cast<unsigned char*>(&vertexData), vertexSize));
	newVertexBuffer->addFormatIdentifier(VertexBuffer::FORMAT_POSITION_2F, 4U);
	newVertexBuffer->addFormatIdentifier(VertexBuffer::FORMAT_TEXTURE_2F, 4U);
	
	Resource<IndexBuffer> newIndexBuffer(new IndexBuffer(reinterpret_cast<unsigned char*>(&indexData), indexSize, IndexBuffer::INDEX_UNSIGNED_BYTE, IndexBuffer::FORMAT_TRIANGLES));
	
	Resource<Material> newMaterial(new Material);
	newMaterial->setShader(mShader);
	newMaterial->addTexture(texture);
	
	return Resource<Mesh>(new Mesh(newVertexBuffer, newIndexBuffer, newMaterial));
}

Resource<Shader> JavaScriptCanvasBinds::makeShader()
{
	std::string vShader =
		"attribute vec4 a_position;								\n"
		"attribute vec2 a_texCoord0;							\n"
		"varying vec2 v_texCoord0;								\n"
		"uniform mat4 u_mvp;									\n"
		"void main()											\n"
		"{														\n"
		"	gl_Position =  u_mvp * a_position;					\n"
		"	v_texCoord0 = a_texCoord0;							\n"
		"}														\n";

	std::string fShader =
		#ifdef GLES2
		"precision mediump float;								\n"
		#endif
		"varying vec2 v_texCoord0;								\n"
		"uniform sampler2D s_texture0;							\n"
		"void main()											\n"
		"{														\n"
		"	gl_FragColor = texture2D(s_texture0, v_texCoord0);	\n"
		"}														\n";

	#ifndef GLES1
		Shader* newShader(new Shader());
		newShader->createFromSource(vShader, fShader);

		return Resource<Shader>(newShader);
	#else
		return 0;
	#endif
}
