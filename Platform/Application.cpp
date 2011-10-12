#include "Application.h"

using namespace GLESGAE;

Application* Application::mInstance = 0;

Application::Application()
: mEventSystem()
, mGraphicsSystem()
, mInputSystem()
, mResourceManager()
, mLifecycle()
, mStateStack()
, mClock()
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

void Application::setLifecycle(const Resource<Lifecycle>& lifecycle)
{
	mLifecycle = lifecycle;
}

void Application::onCreate()
{
	if (mEventSystem == 0)
		mEventSystem = Resource<EventSystem>(new EventSystem);
	if (mInputSystem == 0)
		mInputSystem = Resource<InputSystem>(new InputSystem(mEventSystem));
	if (mResourceManager == 0)
		mResourceManager = Resource<ResourceManager>(new ResourceManager);
	if (mGraphicsSystem == 0)
		mGraphicsSystem = Resource<GraphicsSystem>(new GraphicsSystem());
	if (mStateStack == 0)
		mStateStack = Resource<StateStack>(new StateStack);
	if (mClock == 0)
		mClock = Resource<Clock>(new Clock);
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

	delete mInstance;
}

