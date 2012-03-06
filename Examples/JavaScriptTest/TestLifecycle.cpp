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
#include "../../Input/Pointer.h"
#include "../../Input/Joystick.h"
#include "../../Input/Pad.h"

#include "../../Resources/Resource.h"
#include "../../Resources/ResourceBank.h"
#include "../../Resources/ResourceManager.h"

#include "../../Scripting/JavaScript/JavaScriptContext.h"
#include "../../Scripting/JavaScript/Bindings/JavaScriptBinds.h"
#include "../../Utils/Logger.h"

#include "TestJavaScriptClass.h"
#include "../../File/File.h"
#include "../../Graphics/Camera.h"
#include "../../Graphics/Renderer/GLES10/FixedFunctionGlVARenderer.h"
#include "../../Graphics/State/GLES1/GLES1State.h"

using namespace GLESGAE;

void TestLifecycle::onCreate()
{
	Application* application(Application::getInstance());
	const Resource<GraphicsSystem>& graphicsSystem(application->getGraphicsSystem());
	const Resource<EventSystem>& eventSystem(application->getEventSystem());
	
	if (false == graphicsSystem->initialise("GLESGAE Java Test", 480, 320, 16, false)) {
		//TODO: OH NOES! WE'VE DIEDED!
	}
	
	eventSystem->bindToWindow(graphicsSystem->getCurrentWindow());
	
	Resource<RenderContext> currentContext(graphicsSystem->getCurrentContext());
	mScreenTarget = currentContext->createRenderTarget(RenderTarget::TARGET_SCREEN, RenderTarget::OPTIONS_WITH_COLOUR);
	currentContext->setRenderer(Resource<Renderer>(new FixedFunctionGlVARenderer));
	
	const Resource<JavaScriptContext>& javaContext(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>());
	javaContext->initialise();
	javaContext->addClass(Resource<BaseJavaScriptClass>(new TestJavaScriptClass));
	bindGLESGAEJS();
	
	const Resource<InputSystem>& inputSystem(application->getInputSystem());
	inputSystem->newKeyboard();
	inputSystem->newPointer();
#if defined(PANDORA)
	inputSystem->newJoystick();	// left nub
	inputSystem->newJoystick();	// right nub
	inputSystem->newPad();		// buttons
#endif
	
	// Setup Fixed Function settings
	Resource<GLES1State> currentState(currentContext->getRenderState().recast<GLES1State>());
	currentState->setTexturingEnabled(true);
	currentState->setVertexPositionsEnabled(true);
	currentState->setVertexColoursEnabled(true);
	currentState->setAlphaBlendingEnabled(true);
	currentState->setBlendingFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	Resource<Camera> camera(new Camera(Camera::CAMERA_2D));
	camera->set2dParams(0, 480, 320, 0);
	camera->update();
	currentState->setCamera(camera);
}

void TestLifecycle::onStart()
{
	Application* application(Application::getInstance());
	const Resource<GraphicsSystem>& graphicsSystem(application->getGraphicsSystem());
	const Resource<JavaScriptContext>& javaContext(application->getScriptSystem().recast<JavaScriptContext>());
	File scriptFile("test.js");
	scriptFile.open(FILEIO::OPEN_READ, FILEIO::FILE_ASCII);
	scriptFile.read();
	scriptFile.close();
	
	Resource<RenderContext> currentContext(graphicsSystem->getCurrentContext());
	mScreenTarget->bind();
	currentContext->refresh();
	javaContext->callScript(javaContext->getContext(), scriptFile.stringBuffer());
}

void TestLifecycle::onResume()
{
}

bool TestLifecycle::onLoop()
{
	Application* application(Application::getInstance());
	const Resource<EventSystem>& eventSystem(application->getEventSystem());
	const Resource<InputSystem>& inputSystem(application->getInputSystem());
	const Resource<ScriptSystem>& scriptSystem(application->getScriptSystem());
	Resource<Controller::KeyboardController> myKeyboard(inputSystem->getKeyboard(0));

	eventSystem->update();
	inputSystem->update();
	scriptSystem->update();
	
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
	const Resource<JavaScriptContext>& javaContext(Application::getInstance()->getScriptSystem().recast<JavaScriptContext>());
	javaContext->shutdown();
	mScreenTarget->unbind();
}
