#include "Application.h"

#include "Lifecycle.h"
#include "../Events/EventSystem.h"
#include "../Graphics/GraphicsSystem.h"
#include "../Input/InputSystem.h"
#include "../Resources/ResourceManager.h"
#include "../States/StateStack.h"
#include "../Time/Clock.h"

using namespace GLESGAE;

Application* Application::mInstance = 0;

Application::Application()
: mEventSystem(0)
, mGraphicsSystem(0)
, mInputSystem(0)
, mResourceManager(0)
, mLifecycle(0)
, mStateStack(0)
, mClock(0)
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

void Application::onCreate(const GraphicsSystem::RenderType renderType)
{
	if (0 == mEventSystem)
		mEventSystem = new EventSystem;
	if (0 == mInputSystem)
		mInputSystem = new InputSystem(mEventSystem);
	if (0 == mResourceManager)
		mResourceManager = new ResourceManager;
	if (0 == mGraphicsSystem)
		mGraphicsSystem = new GraphicsSystem(renderType);
	if (0 == mStateStack)
		mStateStack = new StateStack;
	if (0 == mClock)
		mClock = new Clock;
	if (0 != mLifecycle)
		mLifecycle->onCreate();
}

void Application::onStart()
{
	if (0 != mLifecycle)
		mLifecycle->onStart();
}

void Application::onResume()
{
	if (0 != mLifecycle)
		mLifecycle->onResume();
}

bool Application::onLoop()
{
	if (0 != mLifecycle)
		return mLifecycle->onLoop();
	else
		return false;
}

void Application::onPause()
{
	if (0 != mLifecycle)
		mLifecycle->onPause();
}

void Application::onStop()
{
	if (0 != mLifecycle)
		mLifecycle->onStop();
}

void Application::onDestroy()
{
	if (0 != mLifecycle) {
		mLifecycle->onDestroy();
		delete mLifecycle;
		mLifecycle = 0;
	}
		
	if (0 != mEventSystem) {
		delete mEventSystem;
		mEventSystem = 0;
	}
	if (0 != mInputSystem) {
		delete mInputSystem;
		mInputSystem = 0;
	}
	if (0 != mResourceManager) {
		delete mResourceManager;
		mResourceManager = 0;
	}
	if (0 != mGraphicsSystem) {
		delete mGraphicsSystem;
		mGraphicsSystem = 0;
	}
	if (0 != mStateStack) {
		delete mStateStack;
		mStateStack = 0;
	}
	if (0 != mClock) {
		delete mClock;
		mClock = 0;
	}
}

