#ifndef _LIFECYCLE_H_
#define _LIFECYCLE_H_

namespace GLESGAE
{
	class Lifecycle : public BaseLifecycle
	{
		public:
			virtual ~Lifecycle() {}
			
			/// onCreate - Called by the platform as soon as the application is started - IE: To setup Platform specifics.
			virtual void onCreate() = 0;
			
			/// onWindowCreate - Called by the platform once a Window is ready to be used.
			virtual void onWindowCreate() = 0;
			
			/// onStart - Called by the platform once it's initialized - IE: Platform specifics have been setup.
			virtual void onStart() = 0;
			
			/// onResume - Called by the platform when our application has came back from a Paused state.
			virtual void onResume() = 0;
			
			/// onLoop - Called by the platform to generate a new frame of logic.
			virtual bool onLoop() = 0;
			
			/// onPause - Called by the platform before our application must enter a paused state.
			virtual void onPause() = 0;
			
			/// onStop - Called by the platform before our application must enter a stopped state.
			virtual void onStop() = 0;
			
			/// onDestroy - Called by the platform before our application is stopped - IE: to save state, etc...
			virtual void onDestroy() = 0;
	};
}

#endif

