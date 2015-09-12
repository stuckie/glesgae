#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#define PLATFORM_MAIN		 			\
GAE_Platform_t* gPlatform;				\
void main(struct android_app* app) {			\
	GAE_BOOL isApplicationRunning = GAE_TRUE;	\
	int ident = 0;					\
	int events = 0;					\
	struct android_poll_source* source = 0;

#define PLATFORM_INIT					\
	app_dummy();					\
	gPlatform = GAE_Platform_create();		\
	app->userData = gPlatform;			\
	app->onAppCmd = gPlatform->onAppCmd;		\
	app->onInputEvent = gPlatform->onInputEvent;	\
	gPlatform->androidApp = app;			\
							\
	if (0 != app->savedState)			\
		gPlatform->userData = app->savedState;
	
#define PLATFORM_LOOP										\
	gPlatform->parent->onCreate();								\
												\
												\
	while (GAE_TRUE == isApplicationRunning) {						\
		while ( (ident=ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {	\
		if (0 != source) {								\
				source->process(app, source);					\
			}									\
		}										\
		applicationRunning = gPlatform->parent->onLoop();

#define END_MAIN			\
	GAE_Platform_delete(gPlatform);	\
	gPlatform = 0;			\
	return 0;			\
}

typedef struct GAE_Platform_s {
	GAE_Common_Platform_t parent;
	onAppCmd* onAppCmd;
	onInputEvent* onInputEvent;
	struct android_app* androidApp;
	void* userData;
} GAE_Platform_t;

GAE_Platform_t* GAE_Platform_create(void);
void GAE_Platform_destroy(GAE_Platform_t* platform);

#endif
