#include "../../Platform/Application.h"
#include "../../Scripting/JavaScript/JavaScriptContext.h"
#include "TestLifecycle.h"

using namespace GLESGAE;

int main(void)
{
	Application* application(Application::getInstance());
	application->setLifecycle(Resource<Lifecycle>(new TestLifecycle));
	application->setScriptSystem(Resource<ScriptSystem>(new JavaScriptContext));
	
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

