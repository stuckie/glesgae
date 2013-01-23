#include "../Clock.h"

#include <ctime>

double mStartTime(0.0);
double mCurrentTime(0.0);
double mCurrentDelta(0.0);
double mPausedTime(0.0);

bool mIsPaused(false);

using namespace GLESGAE;

double getCurrentTime(const timespec* time);

Clock::Clock()
{
	timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	mStartTime = getCurrentTime(&time);
	mCurrentTime = mStartTime;
}

void Clock::reset()
{
	timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	mStartTime = getCurrentTime(&time);
	mCurrentTime = mStartTime;
}

float Clock::getTime()
{
	timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	mCurrentTime = getCurrentTime(&time);
	mCurrentDelta = mCurrentTime - mStartTime;
	
	return static_cast<float>(mCurrentDelta);
}

void Clock::pause()
{
	timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	mPausedTime = getCurrentTime(&time);
	
	mIsPaused = true;
}

bool Clock::isPaused() const
{
	return mIsPaused;
}

void Clock::resume()
{
	timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	mCurrentTime = getCurrentTime(&time);
	mStartTime += (mCurrentTime - mPausedTime);
	
	mIsPaused = false;
}

double getCurrentTime(const timespec* time)
{
  return (static_cast<double>(time->tv_sec) + static_cast<double>(time->tv_nsec * 0.000000001));
}

