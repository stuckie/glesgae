#include "Timer.h"
#include "Clock.h"

using namespace GLESGAE;

Timer::Timer()
: mLastTime(0.0F)
, mCurrentTime(0.0F)
, mDeltaTime(0.0F)
, mScale(1.0F)
, mPaused(false)
{
}

void Timer::update(Clock* const clock)
{
	mCurrentTime = clock->getTime() * mScale;
	if (false == mPaused)
		mDeltaTime = mCurrentTime - mLastTime;
	else
		mDeltaTime = 0.0F;
	mLastTime = mCurrentTime;
}

