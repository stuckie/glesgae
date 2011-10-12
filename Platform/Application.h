#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Lifecycle.h"
#include "../Resources/Resource.h"
#include "../Events/EventSystem.h"
#include "../Graphics/GraphicsSystem.h"
#include "../Input/InputSystem.h"
#include "../Resources/ResourceManager.h"
#include "../States/StateStack.h"
#include "../Time/Clock.h"

namespace GLESGAE
{
	class Application
	{
		public:
			~Application();
			
			/// Application is a Singleton and can only be accessed via this method.
			static Application* getInstance();
			
			/// Set the user lifecycle
			void setLifecycle(const Resource<Lifecycle>& lifecycle);
			
			// Lifecycle Bits
			/// onCreate - Called by the platform as soon as the application is started - IE: To setup Platform specifics.
			void onCreate();
			
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
			/// Retrieve the Input System
			const Resource<InputSystem>& getInputSystem() { return mInputSystem; }
			
			/// Retrieve the Event System
			const Resource<EventSystem>& getEventSystem() { return mEventSystem; }
			
			/// Retrieve the Graphics System
			const Resource<GraphicsSystem>& getGraphicsSystem() { return mGraphicsSystem; }
			
			/// Retrieve the Resource Manager
			const Resource<ResourceManager>& getResourceManager() { return mResourceManager; }
			
			/// Retrieve the State Stack
			const Resource<StateStack>& getStateStack() { return mStateStack; }
			
			/// Retrieve the System Clock
			const Resource<Clock>& getClock() { return mClock; }
			
		private:
			/// Private constructor as this can only be created and managed through it's singleton.
			Application();
			/// No copying
			Application(const Application&);
			/// No equals operator
			Application& operator=(const Application&);
			
			static Application* mInstance;
			
			Resource<EventSystem> mEventSystem;
			Resource<GraphicsSystem> mGraphicsSystem;
			Resource<InputSystem> mInputSystem;
			Resource<ResourceManager> mResourceManager;
			Resource<Lifecycle> mLifecycle;
			Resource<StateStack> mStateStack;
			Resource<Clock> mClock;
	};
}

#endif

