#include "Application.h"

#include "Lifecycle.h"
#include "Platform.h"
#include "../Events/EventSystem.h"
#include "../Graphics/GraphicsSystem.h"
#include "../Input/InputSystem.h"
#include "../States/StateStack.h"
#include "../Time/Clock.h"
#include "../Utils/Logger.h"
#include "../Plugin/PluginSystem.h"


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
, mPlugins(0)
, mPlatform(0)
{
}

Application::~Application()
{
	if (0 != mEventSystem)
		delete mEventSystem;
	if (0 != mInputSystem)
		delete mInputSystem;
	if (0 != mGraphicsSystem)
		delete mGraphicsSystem;
	if (0 != mStateStack)
		delete mStateStack;
	if (0 != mClock)
		delete mClock;
	if (0 != mLogger)
		delete mLogger;

	for (std::vector<PluginSystem*>::iterator itr(mPlugins.begin()); itr < mPlugins.end(); ++itr)
		delete *itr;
}

Application* Application::getInstance()
{
	if (0 == mInstance)
		mInstance = new Application;
		
	return mInstance;
}

void Application::setPlatform(Platform* const platform)
{
	mPlatform = platform;
}

void Application::setLifecycle(Lifecycle* const lifecycle)
{
	mLifecycle = lifecycle;
}

void Application::addPluginSystem(PluginSystem* const system)
{
	mPlugins.push_back(system);
}

PluginSystem* Application::getPluginSystem(const HashString& system)
{
	for (std::vector<PluginSystem*>::iterator itr(mPlugins.begin()); itr < mPlugins.end(); ++itr) {
		if ((*itr)->getName() == system)
			return *itr;
	}

	return 0;
}

void Application::onCreate()
{
	if (0 == mLogger)
		mLogger = new Logger;
	if (0 == mEventSystem)
		mEventSystem = new EventSystem;
	if (0 == mInputSystem)
		mInputSystem = new InputSystem(mEventSystem);
	if (0 == mGraphicsSystem)
		mGraphicsSystem = new GraphicsSystem();
	if (0 == mStateStack)
		mStateStack = new StateStack;
	if (0 == mClock)
		mClock = new Clock;
	if (0 != mLifecycle)
		mLifecycle->onCreate();
}

void Application::onWindowCreate()
{
	if (0 != mLifecycle)
		mLifecycle->onWindowCreate();
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
	if (0 != mLifecycle)
		mLifecycle->onDestroy();
	
	mLifecycle = 0;
	mPlatform = 0;

	if (0 != mInstance) {
		delete mInstance;
		mInstance = 0;
	}
}
