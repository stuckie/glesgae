#if defined(ANDROID) && !defined(SDL)

#include <android_native_app_glue.h>

#include "../../Graphics/Window/Android/AndroidRenderWindow.h"
#include "../EventSystem.h"
#include "../Event.h"

typedef struct GAE_Android_EventSystem_s {
	GAE_Android_RenderWindow_t* window;
} GAE_Android_EventSystem_t;

GAE_EventSystem_t* GAE_EventSystem_create(GAE_RenderWindow_t* const window) {
	GAE_EventSystem_t* system = malloc(sizeof(GAE_EventSystem_t));
	GAE_X11_EventSystem_t* userData = malloc(sizeof(GAE_EventSystem_t));

	userData->window = (GAE_Android_RenderWindow_t*)window;
	system->userData = (void*)userData;
	system->observers = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(GAE_Array_t), GAE_HashString_compare);
	system->triggers = GAE_Map_create(sizeof(GAE_HashString_t), sizeof(GAE_Array_t), GAE_HashString_compare);

	return system;
}

void GAE_EventSystem_update(GAE_EventSystem_t* /*system*/) {

}

/* Platform specific delete function */
void GAE_EventSystem_delete(GAE_EventSystem_t* system) {
	if (0 != system->userData) {
		free(system->userData);
		system->userData = 0;
	}

	GAE_Map_delete(system->observers);
	GAE_Map_delete(system->triggers);

	system->observers = 0;
	system->triggers = 0;

	free(system);
	system = 0;
}


int32_t handleAndroidInput(struct android_app* /*app*/, AInputEvent* /*event*/) {
	if (AINPUT_EVENT_TYPE_MOTION == AInputEvent_getType(event)) {
	/*
		engine->state.x = AMotionEvent_getX(event, 0);
		engine->state.y = AMotionEvent_getY(event, 0);
	*/	return 1;
	}
	
	return 0;
}

void handleAndroidCommand(struct android_app* /*app*/, int32_t /*command*/) {
	switch (command) {
		/**
		* Command from main thread: the AInputQueue has changed.  Upon processing
		* this command, android_app->inputQueue will be updated to the new queue
		* (or NULL).
		*/
		case APP_CMD_INPUT_CHANGED: {
			
		}
		break;

		/**
		* Command from main thread: a new ANativeWindow is ready for use.  Upon
		* receiving this command, android_app->window will contain the new window
		* surface.
		*/
		case APP_CMD_INIT_WINDOW: {

		}
		break;
		
		/**
		* Command from main thread: the existing ANativeWindow needs to be
		* terminated.  Upon receiving this command, android_app->window still
		* contains the existing window; after calling android_app_exec_cmd
		* it will be set to NULL.
		*/
		case APP_CMD_TERM_WINDOW: {
			
		}
		break;

		/**
		* Command from main thread: the current ANativeWindow has been resized.
		* Please redraw with its new size.
		*/
		case APP_CMD_WINDOW_RESIZED: {
			
		}
		break;

		/**
		* Command from main thread: the system needs that the current ANativeWindow
		* be redrawn.  You should redraw the window before handing this to
		* android_app_exec_cmd() in order to avoid transient drawing glitches.
		*/
		case APP_CMD_WINDOW_REDRAW_NEEDED: {
			
		}
		break;

		/**
		* Command from main thread: the content area of the window has changed,
		* such as from the soft input window being shown or hidden.  You can
		* find the new content rect in android_app::contentRect.
		*/
		case APP_CMD_CONTENT_RECT_CHANGED: {
			
		}
		break;
		

		/**
		* Command from main thread: the app's activity window has gained
		* input focus.
		*/
		case APP_CMD_GAINED_FOCUS: {
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
			/*
			 When our app loses focus, we stop monitoring the accelerometer.
			 This is to avoid consuming battery while not being used.
			if (engine->accelerometerSensor != NULL) {
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
			
		}
		break;

		/**
		* Command from main thread: the system is running low on memory.
		* Try to reduce your memory use.
		*/
		case APP_CMD_LOW_MEMORY: {
			
		}
		break;

		/**
		* Command from main thread: the app's activity has been started.
		*/
		case APP_CMD_START: {
			
		}
		break;

		/**
		* Command from main thread: the app's activity has been resumed.
		*/
		case APP_CMD_RESUME: {
			
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
			
		}
		break;

		/**
		* Command from main thread: the app's activity has been stopped.
		*/
		case APP_CMD_STOP: {
			
		}
		break;

		/**
		* Command from main thread: the app's activity is being destroyed,
		* and waiting for the app thread to clean up and exit before proceeding.
		*/
		case APP_CMD_DESTROY: {
			
		}
		break;
	}
}

#endif
