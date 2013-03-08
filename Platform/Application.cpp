#include "Application.h"

#include "Lifecycle.h"
#include "../Events/EventSystem.h"
#include "../Graphics/GraphicsSystem.h"
#include "../Input/InputSystem.h"
#include "../States/StateStack.h"
#include "../Time/Clock.h"
#include "../Utils/Logger.h"
#include "../Scripting/ScriptSystem.h"


using namespace GLESGAE;

Application* Application::mInstance = 0;

Application::Application()
: mEventSystem(0)
, mGraphicsSystem(0)
, mInputSystem(0)
, mLifecycle(0)
, mStateStack(0)
, mClock(0)
, mLogger(0)
, mScriptSystem(0)
{
}

Application::~Application()
{
}

Application* Application::getInstance()
{
	if (0 == mInstance)
		mInstance = new Application;
		
	return mInstance;
}

void Application::setLifecycle(Lifecycle* const lifecycle)
{
	mLifecycle = lifecycle;
}

void Application::setScriptSystem(ScriptSystem* const scriptSystem)
{
	mScriptSystem = scriptSystem;
}

void Application::onCreate()
{
	if (mLogger == 0)
		mLogger = new Logger;
	if (mEventSystem == 0)
		mEventSystem = new EventSystem;
	if (mInputSystem == 0)
		mInputSystem = new InputSystem(mEventSystem);
	if (mGraphicsSystem == 0)
		mGraphicsSystem = new GraphicsSystem();
	if (mStateStack == 0)
		mStateStack = new StateStack;
	if (mClock == 0)
		mClock = new Clock;
	if (mLifecycle != 0)
		mLifecycle->onCreate();
}

void Application::onStart()
{
	if (mLifecycle != 0)
		mLifecycle->onStart();
}

void Application::onResume()
{
	if (mLifecycle != 0)
		mLifecycle->onResume();
}

bool Application::onLoop()
{
	if (mLifecycle != 0)
		return mLifecycle->onLoop();
	else
		return false;
}

void Application::onPause()
{
	if (mLifecycle != 0)
		mLifecycle->onPause();
}

void Application::onStop()
{
	if (mLifecycle != 0)
		mLifecycle->onStop();
}

void Application::onDestroy()
{
	if (mLifecycle != 0)
		mLifecycle->onDestroy();

	if (0 != mInstance) {
		delete mInstance;
		mInstance = 0;
	}
}

