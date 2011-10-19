#ifndef _TIMER_H_
#define _TIMER_H_

#include "../Resources/Resource.h"

namespace GLESGAE
{
	//! Timers can read from a Clock and scale the time as it sees fit.
	//! This is useful to have things like Physics run faster/slower than the Graphics.
	class Clock;
	class Timer
	{
		public:
			Timer();
			
			/// Return the current time according to this Timer.
			float getTime() const { return mCurrentTime; }
			
			/// Return the current deltaTime according to this Timer.
			float getDelta() const { return mDeltaTime; }
			
			/// Pause the Timer.
			void pause() { mPaused = true; }
			
			/// Is this Timer paused?
			bool isPaused() const { return mPaused; }
			
			/// Resume the Timer.
			void resume() { mPaused = false; }
			
			/// Set the scale of this Timer.
			void setScale(const float scale) { mScale = scale; }
			
			/// Return the scale of this Timer.
			float getScale() const { return mScale; }
			
			/// Update to this Clock - should be done only once per frame.
			void update(const Resource<Clock>& clock);
			
			/// Reset the timer
			void reset();
			
		private:
			float mLastTime;
			float mCurrentTime;
			float mDeltaTime;
			float mScale;
			bool mPaused;
	};
}

#endif

