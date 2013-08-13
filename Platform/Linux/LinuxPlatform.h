#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#define PLATFORM_MAIN 						\
int main(void)							\
{								

#define PLATFORM_INIT
	
#define PLATFORM_LOOP						\
	application->onCreate();				\
	application->onWindowCreate();				\
	application->onStart();					\
	application->onResume();				\
								\
	bool applicationRunning(true);				\
	while (true == applicationRunning)			\
		applicationRunning = application->onLoop();	\
								\
	application->onPause();					\
	application->onStop();					\
	application->onDestroy();				\

#define END_MAIN						\
	return 0;						\
}

namespace GLESGAE
{
	class Platform : public BasePlatform
	{
		public:
			virtual ~Platform() {}
			
	};
}

#endif

