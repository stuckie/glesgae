#include "TestLifecycle.h"

#include "../../Platform/Application.h"

#include "../../Graphics/GraphicsSystem.h"

#if defined(LINUX)
	#include "../../Graphics/Platform/Linux/LinuxRenderPlatform.h"
#elif defined(PANDORA)
	#include "../../Graphics/Platform/Pandora/PandoraRenderPlatform.h"
#elif defined(ANDROID)
	#include "../../Graphics/Platform/Android/AndroidRenderContext.h"
#elif defined(IOS)
	#include "../../Graphics/Platform/iOS/iOSRenderPlatform.h"
#endif

#include "../../Events/EventSystem.h"
#include "../../Input/InputSystem.h"
#include "../../Input/Keyboard.h"

#include "../../Resources/Resource.h"
#include "../../Resources/ResourceBank.h"
#include "../../Resources/ResourceManager.h"

#include "../../Scripting/JavaScriptContext.h"
#include "../../Utils/Logger.h"

#include "TestJavaScriptClass.h"

#include <cstdio>
#include "../../Graphics/Renderer/GLES11/FixedFunctionGlVboRenderer.h"
#include "../../Graphics/State/GLES1/GLES1State.h"

using namespace GLESGAE;

void TestLifecycle::onCreate()
{
	Application* application(Application::getInstance());
	const Resource<GraphicsSystem>& graphicsSystem(application->getGraphicsSystem());
	const Resource<EventSystem>& eventSystem(application->getEventSystem());
	
	if (false == graphicsSystem->initialise("GLESGAE Application Lifecycle Test", 800, 480, 16, false)) {
		//TODO: OH NOES! WE'VE DIEDED!
	}
	
	eventSystem->bindToWindow(graphicsSystem->getCurrentWindow());
	
	Resource<RenderContext> currentContext(graphicsSystem->getCurrentContext());
	mScreenTarget = currentContext->createRenderTarget(RenderTarget::TARGET_SCREEN, RenderTarget::OPTIONS_WITH_COLOUR);
	currentContext->setRenderer(Resource<Renderer>(new FixedFunctionGlVboRenderer));
	JavaScriptContext::getInstance().addClass(Resource<BaseJavaScriptClass>(new TestJavaScriptClass));
	
	const Resource<InputSystem>& inputSystem(application->getInputSystem());
	inputSystem->newKeyboard();
	
	// Setup Fixed Function settings
	Resource<GLES1State> currentState(currentContext->getRenderState().recast<GLES1State>());
	currentState->setTexturingEnabled(true);
	currentState->setVertexPositionsEnabled(true);
}

void TestLifecycle::onStart()
{
	JavaScriptContext& javaContext(JavaScriptContext::getInstance());
	Logger::getInstance().log("onStart\n", Logger::LOG_TYPE_INFO);
	Logger::getInstance().log(javaContext.valueToString(javaContext.callScript("\"Hello, JavaScriptCore!\";")) + "\n", Logger::LOG_TYPE_INFO);
	javaContext.callScript("var testClass = new glesgae.TestJavaScriptClass(); testClass.doABarrelRoll();");
}

void TestLifecycle::onResume()
{
}

bool TestLifecycle::onLoop()
{
	Application* application(Application::getInstance());
	const Resource<EventSystem>& eventSystem(application->getEventSystem());
	const Resource<InputSystem>& inputSystem(application->getInputSystem());
	const Resource<GraphicsSystem>& graphicsSystem(application->getGraphicsSystem());
	Resource<RenderContext> currentContext(graphicsSystem->getCurrentContext());
	
	Controller::KeyboardController* myKeyboard(inputSystem->getKeyboard(0));

	eventSystem->update();
	inputSystem->update();
	
	mScreenTarget->bind();
	currentContext->refresh();
	mScreenTarget->unbind();
	
	return !(myKeyboard->getKey(Controller::KEY_ESCAPE));
}

void TestLifecycle::onPause()
{
}

void TestLifecycle::onStop()
{
}

void TestLifecycle::onDestroy()
{
}

