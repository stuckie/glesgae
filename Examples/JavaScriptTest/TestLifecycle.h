#ifndef _TEST_LIFECYCLE_H_
#define _TEST_LIFECYCLE_H_

#include "../../Platform/Lifecycle.h"
#include "../../Resources/Resource.h"
#include "../../Graphics/Target/RenderTarget.h"

class TestLifecycle : public GLESGAE::Lifecycle
{
	public:
		TestLifecycle() : GLESGAE::Lifecycle(), mScreenTarget() {}
		~TestLifecycle() {}
		
		/// Called directly after the system has started
		void onCreate();
		
		/// Called when starting up for the first time
		void onStart();
		
		/// Called when resuming from either pause or continuing from startup
		void onResume();
		
		/// Call one frame of logic
		bool onLoop();
		
		/// Called when going into a platform pause state
		void onPause();
		
		/// Called when the platform wants us to sleep completely
		void onStop();
		
		/// Called when the platform wants us to close
		void onDestroy();
		
	private:
		GLESGAE::Resource<GLESGAE::RenderTarget> mScreenTarget;
};

#endif

