#if defined(ANDROID)

#include "../../Utils/Logger.h"
#include "../../Platform/Application.h"
#include "../../Graphics/Window/Android/AndroidRenderWindow.h"
#include "../EventSystem.h"
#include "../EventTypes.h"
#include "../SystemEvents.h"
#include "AndroidEvents.h"

using namespace GLESGAE;

EventSystem::EventSystem()
: CommonEventSystem()
, mActive(true)
, mWindow()
{
	// Register System Events
	registerEventType(SystemEvents::App::Started);
	registerEventType(SystemEvents::App::Paused);
	registerEventType(SystemEvents::App::Resumed);
	registerEventType(SystemEvents::App::Destroyed);

	registerEventType(SystemEvents::Window::Opened);
	registerEventType(SystemEvents::Window::Resized);
	registerEventType(SystemEvents::Window::Closed);

	// Register Android Specific Events
	registerEventType(AndroidEvents::Input::Touch::Moved);
	registerEventType(AndroidEvents::Input::Touch::TouchDown);
	registerEventType(AndroidEvents::Input::Touch::TouchUp);

	registerEventType(AndroidEvents::Input::Keyboard::KeyDown);
	registerEventType(AndroidEvents::Input::Keyboard::KeyUp);
}

EventSystem::~EventSystem()
{

}

void EventSystem::bindToWindow(RenderWindow* const window)
{
	mWindow = reinterpret_cast<AndroidRenderWindow*>(window);
}


void EventSystem::update()
{
	
}

int32_t EventSystem::handleAndroidInput(struct android_app* app, AInputEvent* event)
{
	Application* application(reinterpret_cast<Application*>(app->userData));
	if (AINPUT_EVENT_TYPE_MOTION == AInputEvent_getType(event)) {
		//engine->state.x = AMotionEvent_getX(event, 0);
		//engine->state.y = AMotionEvent_getY(event, 0);
		//return 1;
	}
	
	return 0;
}

void EventSystem::handleAndroidCommand(struct android_app* app, int32_t command)
{
	Application* application(reinterpret_cast<Application*>(app->userData));
	switch (command) {
		/**
		* Command from main thread: the AInputQueue has changed.  Upon processing
		* this command, android_app->inputQueue will be updated to the new queue
		* (or NULL).
		*/
		case APP_CMD_INPUT_CHANGED: {
			application->getLogger()->log("Android Command: Input Queue Changed\n", Logger::LOG_TYPE_INFO);
		}
		break;

		/**
		* Command from main thread: a new ANativeWindow is ready for use.  Upon
		* receiving this command, android_app->window will contain the new window
		* surface.
		*/
		case APP_CMD_INIT_WINDOW: {
			application->getLogger()->log("Android Command: Window Init\n", Logger::LOG_TYPE_INFO);
			application->onWindowCreate();
		}
		break;
		
		/**
		* Command from main thread: the existing ANativeWindow needs to be
		* terminated.  Upon receiving this command, android_app->window still
		* contains the existing window; after calling android_app_exec_cmd
		* it will be set to NULL.
		*/
		case APP_CMD_TERM_WINDOW: {
			application->getLogger()->log("Android Command: Window Term\n", Logger::LOG_TYPE_INFO);
		}
		break;

		/**
		* Command from main thread: the current ANativeWindow has been resized.
		* Please redraw with its new size.
		*/
		case APP_CMD_WINDOW_RESIZED: {
			application->getLogger()->log("Android Command: Window Resized\n", Logger::LOG_TYPE_INFO);
		}
		break;

		/**
		* Command from main thread: the system needs that the current ANativeWindow
		* be redrawn.  You should redraw the window before handing this to
		* android_app_exec_cmd() in order to avoid transient drawing glitches.
		*/
		case APP_CMD_WINDOW_REDRAW_NEEDED: {
			application->getLogger()->log("Android Command: Window Needs Redraw\n", Logger::LOG_TYPE_INFO);
		}
		break;

		/**
		* Command from main thread: the content area of the window has changed,
		* such as from the soft input window being shown or hidden.  You can
		* find the new content rect in android_app::contentRect.
		*/
		case APP_CMD_CONTENT_RECT_CHANGED: {
			application->getLogger()->log("Android Command: Window Focus Changed\n", Logger::LOG_TYPE_INFO);
		}
		break;
		

		/**
		* Command from main thread: the app's activity window has gained
		* input focus.
		*/
		case APP_CMD_GAINED_FOCUS: {
			application->getLogger()->log("Android Command: App Focus Gained\n", Logger::LOG_TYPE_INFO);
			/*if (engine->accelerometerSensor != NULL) {
				ASensorEventQueue_enableSensor(engine->sensorEventQueue,
					engine->accelerometerSensor);
				// We'd like to get 60 events per second (in us).
				ASensorEventQueue_setEventRate(engine->sensorEventQueue,
					engine->accelerometerSensor, (1000L/60)*1000);
			}*/
		}
		break;

		/**
		* Command from main thread: the app's activity window has lost
		* input focus.
		*/
		case APP_CMD_LOST_FOCUS: {
			application->getLogger()->log("Android Command: App Focus Lost\n", Logger::LOG_TYPE_INFO);
			// When our app loses focus, we stop monitoring the accelerometer.
			// This is to avoid consuming battery while not being used.
			/*if (engine->accelerometerSensor != NULL) {
				ASensorEventQueue_disableSensor(engine->sensorEventQueue,
					engine->accelerometerSensor);
			}
			// Also stop animating.
			engine->animating = 0;
			engine_draw_frame(engine);
			*/
		}
		break;

		/**
		* Command from main thread: the current device configuration has changed.
		*/
		case APP_CMD_CONFIG_CHANGED: {
			application->getLogger()->log("Android Command: Config Changed\n", Logger::LOG_TYPE_INFO);
		}
		break;

		/**
		* Command from main thread: the system is running low on memory.
		* Try to reduce your memory use.
		*/
		case APP_CMD_LOW_MEMORY: {
			application->getLogger()->log("Android Command: Low Memory\n", Logger::LOG_TYPE_INFO);
		}
		break;

		/**
		* Command from main thread: the app's activity has been started.
		*/
		case APP_CMD_START: {
			application->getLogger()->log("Android Command: onStart\n", Logger::LOG_TYPE_INFO);
			application->onStart();
		}
		break;

		/**
		* Command from main thread: the app's activity has been resumed.
		*/
		case APP_CMD_RESUME: {
			application->getLogger()->log("Android Command: onResume\n", Logger::LOG_TYPE_INFO);
			application->onResume();
		}
		break;

		/**
		* Command from main thread: the app should generate a new saved state
		* for itself, to restore from later if needed.  If you have saved state,
		* allocate it with malloc and place it in android_app.savedState with
		* the size in android_app.savedStateSize.  The will be freed for you
		* later.
		*/
		case APP_CMD_SAVE_STATE: {
			application->getLogger()->log("Android Command: Save State\n", Logger::LOG_TYPE_INFO);
			/*engine->app->savedState = malloc(sizeof(struct saved_state));
			*((struct saved_state*)engine->app->savedState) = engine->state;
			engine->app->savedStateSize = sizeof(struct saved_state);
			*/
		}
		break;

		/**
		* Command from main thread: the app's activity has been paused.
		*/
		case APP_CMD_PAUSE: {
			application->getLogger()->log("Android Command: onPause\n", Logger::LOG_TYPE_INFO);
			application->onPause();
		}
		break;

		/**
		* Command from main thread: the app's activity has been stopped.
		*/
		case APP_CMD_STOP: {
			application->getLogger()->log("Android Command: onStop\n", Logger::LOG_TYPE_INFO);
			application->onStop();
		}
		break;

		/**
		* Command from main thread: the app's activity is being destroyed,
		* and waiting for the app thread to clean up and exit before proceeding.
		*/
		case APP_CMD_DESTROY: {
			application->getLogger()->log("Android Command: onDestroy\n", Logger::LOG_TYPE_INFO);
			application->onDestroy();
		}
		break;
	}
}

#endif
