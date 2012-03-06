#include "JavaScriptTimedFunction.h"

#include "../../Platform/Application.h"
#include "../../Time/Clock.h"
#include "BaseJavaScriptClass.h"
#include "JavaScriptContext.h"

#include <cstdio>

using namespace GLESGAE;

JavaScriptTimedFunction::JavaScriptTimedFunction(const float callbackTime, JSObjectRef callback, const bool recurring)
: mTimer()
, mRecurring(recurring)
, mCallbackTime(callbackTime * 0.001)
, mFunction(callback)
{
}

JavaScriptTimedFunction::JavaScriptTimedFunction(const JavaScriptTimedFunction& rhs)
: mTimer(rhs.mTimer)
, mRecurring(rhs.mRecurring)
, mCallbackTime(rhs.mCallbackTime)
, mFunction(rhs.mFunction)
{
}

JavaScriptTimedFunction& JavaScriptTimedFunction::operator=(const JavaScriptTimedFunction& rhs)
{
	if (this != &rhs) {
		mTimer = rhs.mTimer;
		mRecurring = rhs.mRecurring;
		mFunction = rhs.mFunction;
		mCallbackTime = rhs.mCallbackTime;
	}

	return *this;
}

bool JavaScriptTimedFunction::update()
{
	Application* application(Application::getInstance());
	const Resource<Clock> clock(application->getClock());
	
	mTimer.update(clock);
	if (mTimer.getTime() >= mCallbackTime) {
		const Resource<JavaScriptContext> javaContext(application->getScriptSystem().recast<JavaScriptContext>());
		JSObjectCallAsFunction(javaContext->getContext(), mFunction, 0, 0, 0, 0);
		mTimer.reset();
		return mRecurring;
	}
	
	return true;
}
