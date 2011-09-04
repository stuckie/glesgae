#include "../../Platform/Application.h"
#include "TestLifecycle.h"

using namespace GLESGAE;

int main(void)
{
	Application* application(Application::getInstance());
	application->setLifecycle(new TestLifecycle);
	
	#if defined(GLES1)
		application->onCreate(GraphicsSystem::FIXED_FUNCTION_RENDERING);
	#elif defined(GLES2)
		application->onCreate(GraphicsSystem::SHADER_BASED_RENDERING);
	#elif defined(GLX)
		application->onCreate(GraphicsSystem::SHADER_BASED_RENDERING);
	#endif
	
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

