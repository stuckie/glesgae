#ifndef _CLOCK_H_
#define _CLOCK_H_

namespace GLESGAE
{
	//! Clocks grab the raw system time.
	//! These are platform specific.
	class Clock
	{
		public:
			Clock();
			
			/// Reset the Clock.
			void reset();
			
			/// Return the current delta time.
			float getTime();
			
			/// Pause the Clock.
			void pause();
			
			/// Is the Clock paused?
			bool isPaused() const;
			
			/// Resume the Clock.
			void resume();
	};
}

#endif

