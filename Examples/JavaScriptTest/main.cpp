#include "../../Platform/Application.h"
#include "TestLifecycle.h"

using namespace GLESGAE;

int main(void)
{
	Application* application(Application::getInstance());
	application->setLifecycle(Resource<Lifecycle>(new TestLifecycle));
	
	application->onCreate();	
	application->onStart();
	application->onResume();
	
	bool applicationRunning(true);
	while (true == applicationRunning)
		applicationRunning = application->onLoop();
		
	application->onPause();
	application->onStop();
	application->onDestroy();
	
	return 0;
}

