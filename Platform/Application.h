#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "../Utils/HashString.h"
#include <vector>

namespace GLESGAE
{
	class Platform;
	class PluginSystem;
	class Logger;
	class Clock;
	class StateStack;
	class InputSystem;
	class EventSystem;
	class GraphicsSystem;
	class Lifecycle;
	class Application
	{
		public:
			~Application();
			
			/// Application is a Singleton and can only be accessed via this method.
			static Application* getInstance();
			
			/// Set the user lifecycle
			void setLifecycle(Lifecycle* const lifecycle);
			
			/// Add a Plugin System
			void addPluginSystem(PluginSystem* const system);
			
			/// Set the Platform class
			void setPlatform(Platform* const platform);
			
			// Lifecycle Bits
			/// onCreate - Called by the platform as soon as the application is started - IE: To setup Platform specifics.
			void onCreate();
			
			/// onWindowCreate - Called by the platform as soon as a Window is created - so no Render contexts can be made until this point.
			void onWindowCreate();
			
			/// onStart - Called by the platform once it's initialized - IE: Platform specifics have been setup.
			void onStart();
			
			/// onResume - Called by the platform when our application has came back from a Paused state.
			void onResume();
			
			/// onLoop - Called by the platform to generate a new frame of logic.
			bool onLoop();
			
			/// onPause - Called by the platform before our application must enter a paused state.
			void onPause();
			
			/// onStop - Called by the platform before our application must enter a stopped state.
			void onStop();
			
			/// onDestroy - Called by the platform before our application is stopped - IE: to save state, etc...
			void onDestroy();
			
			// Retrieve Systems
			/// Retrieve any specialised Platform interface
			Platform* getPlatform() { return mPlatform; }
			
			/// Retrieve the Input System
			InputSystem* getInputSystem() { return mInputSystem; }
			
			/// Retrieve the Event System
			EventSystem* getEventSystem() { return mEventSystem; }
			
			/// Retrieve the Graphics System
			GraphicsSystem* getGraphicsSystem() { return mGraphicsSystem; }
			
			/// Retrieve the State Stack
			StateStack* getStateStack() { return mStateStack; }
			
			/// Retrieve the System Clock
			Clock* getClock() { return mClock; }
			
			/// Retrieve the Logger
			Logger* getLogger() { return mLogger; }
			
			/// Retrieve a Plugin System
			PluginSystem* getPluginSystem(const HashString& system);
			
		private:
			/// Private constructor as this can only be created and managed through it's singleton.
			Application();
			/// No copying
			Application(const Application&);
			/// No equals operator
			Application& operator=(const Application&);
			
			static Application* mInstance;
			
			EventSystem* mEventSystem;
			GraphicsSystem* mGraphicsSystem;
			InputSystem* mInputSystem;
			Lifecycle* mLifecycle;
			StateStack* mStateStack;
			Clock* mClock;
			Logger* mLogger;
			std::vector<PluginSystem*> mPlugins;
			Platform* mPlatform;
	};
}

#endif
