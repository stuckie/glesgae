#include "TestJavaScriptClass.h"
#include "../../../Platform/Application.h"

using namespace GLESGAE;

TestJavaScriptClass::TestJavaScriptClass()
: JavaScriptClass<TestJavaScriptClass>("TestJavaScriptClass")
{
	addMethod("doABarrelRoll", &doABarrelRoll);
}

JSValueRef TestJavaScriptClass::doABarrelRoll(JSContextRef /*context*/, JSObjectRef /*function*/, JSObjectRef /*thisObject*/, size_t /*argumentCount*/, const JSValueRef /*arguments*/[], JSValueRef* /*exception*/)
{
	Application::getInstance()->getLogger()->log("Barrel Roll!\n", Logger::LOG_TYPE_INFO);
	
	return 0;
}
