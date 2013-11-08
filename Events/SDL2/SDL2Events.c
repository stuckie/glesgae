#include "SDL2Events.h"

#include "../../Utils/HashString.h"

GAE_HashString_t GAE_EVENT_KEYBOARD;

GAE_HashString_t GAE_EVENT_MOUSE_MOTION;
GAE_HashString_t GAE_EVENT_MOUSE_BUTTON;
GAE_HashString_t GAE_EVENT_MOUSE_WHEEL;

GAE_HashString_t GAE_EVENT_JOYSTICK_AXIS;
GAE_HashString_t GAE_EVENT_JOYSTICK_HAT;
GAE_HashString_t GAE_EVENT_JOYSTICK_BUTTON;
GAE_HashString_t GAE_EVENT_JOYSTICK_BALL;
GAE_HashString_t GAE_EVENT_JOYSTICK_DEVICE;

GAE_HashString_t GAE_EVENT_CONTROLLER_MOTION;
GAE_HashString_t GAE_EVENT_CONTROLLER_BUTTON;
GAE_HashString_t GAE_EVENT_CONTROLLER_DEVICE;

GAE_HashString_t GAE_EVENT_TOUCH;
GAE_HashString_t GAE_EVENT_MULTIGESTURE;
GAE_HashString_t GAE_EVENT_DOLLARGESTURE;

GAE_HashString_t GAE_EVENT_WINDOW_SHOWN;
GAE_HashString_t GAE_EVENT_WINDOW_HIDDEN;
GAE_HashString_t GAE_EVENT_WINDOW_EXPOSED;
GAE_HashString_t GAE_EVENT_WINDOW_MOVED;
GAE_HashString_t GAE_EVENT_WINDOW_RESIZED;
GAE_HashString_t GAE_EVENT_WINDOW_MINIMISED;
GAE_HashString_t GAE_EVENT_WINDOW_MAXIMISED;
GAE_HashString_t GAE_EVENT_WINDOW_RESTORED;
GAE_HashString_t GAE_EVENT_WINDOW_ENTER;
GAE_HashString_t GAE_EVENT_WINDOW_LEAVE;
GAE_HashString_t GAE_EVENT_WINDOW_CLOSED;

GAE_HashString_t GAE_EVENT_FOCUS_GAINED;
GAE_HashString_t GAE_EVENT_FOCUS_LOST;

GAE_HashString_t GAE_EVENT_APP_DESTROYED;

GAE_HashString_t GAE_EVENT_USER_EVENT;

GAE_HashString_t GAE_EVENT_FILE_DROPPED;

GAE_HashString_t GAE_HASH_EVENT;
GAE_HashString_t GAE_HASH_WINDOW;
GAE_HashString_t GAE_HASH_X;
GAE_HashString_t GAE_HASH_Y;
GAE_HashString_t GAE_HASH_WIDTH;
GAE_HashString_t GAE_HASH_HEIGHT;
GAE_HashString_t GAE_HASH_TYPE;
GAE_HashString_t GAE_HASH_CODE;
GAE_HashString_t GAE_HASH_DATA1;
GAE_HashString_t GAE_HASH_DATA2;
GAE_HashString_t GAE_HASH_FILE;

void GAE_Events_create(void) {
	GAE_EVENT_KEYBOARD = GAE_HashString_create("Input::Keyboard");
	
	GAE_EVENT_MOUSE_MOTION = GAE_HashString_create("Input::Mouse::Motion");
	GAE_EVENT_MOUSE_BUTTON = GAE_HashString_create("Input::Mouse::Button");
	GAE_EVENT_MOUSE_WHEEL = GAE_HashString_create("Input::Mouse::Wheel");
	
	GAE_EVENT_JOYSTICK_AXIS = GAE_HashString_create("Input::Joystick::Axis");
	GAE_EVENT_JOYSTICK_HAT = GAE_HashString_create("Input::Joystick::Hat");
	GAE_EVENT_JOYSTICK_BUTTON = GAE_HashString_create("Input::Joystick::Button");
	GAE_EVENT_JOYSTICK_BALL = GAE_HashString_create("Input::Joystick::Ball");
	GAE_EVENT_JOYSTICK_DEVICE = GAE_HashString_create("Input::Joystick::Device");
	
	GAE_EVENT_CONTROLLER_MOTION = GAE_HashString_create("Input::Controller::Motion");
	GAE_EVENT_CONTROLLER_BUTTON = GAE_HashString_create("Input::Controller::Button");
	GAE_EVENT_CONTROLLER_DEVICE = GAE_HashString_create("Input:Controller::Device");
	
	GAE_EVENT_TOUCH = GAE_HashString_create("Input::Touch");
	GAE_EVENT_MULTIGESTURE = GAE_HashString_create("Input::MultiGesture");
	GAE_EVENT_DOLLARGESTURE = GAE_HashString_create("Input::DollarGesture");
	
	GAE_EVENT_WINDOW_SHOWN = GAE_HashString_create("Window::Shown");
	GAE_EVENT_WINDOW_HIDDEN = GAE_HashString_create("Window::Hidden");
	GAE_EVENT_WINDOW_EXPOSED = GAE_HashString_create("Window::Exposed");
	GAE_EVENT_WINDOW_MOVED = GAE_HashString_create("Window::Moved");
	GAE_EVENT_WINDOW_RESIZED = GAE_HashString_create("Window::Resized");
	GAE_EVENT_WINDOW_MINIMISED = GAE_HashString_create("Window::Minimised");
	GAE_EVENT_WINDOW_MAXIMISED = GAE_HashString_create("Window::Maximised");
	GAE_EVENT_WINDOW_RESTORED = GAE_HashString_create("Window::Restored");
	GAE_EVENT_WINDOW_ENTER = GAE_HashString_create("Window::Enter");
	GAE_EVENT_WINDOW_LEAVE = GAE_HashString_create("Window::Leave");
	GAE_EVENT_WINDOW_CLOSED = GAE_HashString_create("Window::Closed");
	
	GAE_EVENT_FOCUS_GAINED = GAE_HashString_create("Focus::Gained");
	GAE_EVENT_FOCUS_LOST = GAE_HashString_create("Focus::Lost");
	
	GAE_EVENT_APP_DESTROYED = GAE_HashString_create("App::Destroyed");
	
	GAE_EVENT_USER_EVENT = GAE_HashString_create("User::Event");
	
	GAE_EVENT_FILE_DROPPED = GAE_HashString_create("File::Dropped");
	
	GAE_HASH_EVENT = GAE_HashString_create("Event");
	GAE_HASH_WINDOW = GAE_HashString_create("Window");
	GAE_HASH_X = GAE_HashString_create("x");
	GAE_HASH_Y = GAE_HashString_create("y");
	GAE_HASH_WIDTH = GAE_HashString_create("width");
	GAE_HASH_HEIGHT = GAE_HashString_create("height");
	GAE_HASH_TYPE = GAE_HashString_create("type");
	GAE_HASH_CODE = GAE_HashString_create("code");
	GAE_HASH_DATA1 = GAE_HashString_create("data1");
	GAE_HASH_DATA2 = GAE_HashString_create("data2");
	GAE_HASH_FILE = GAE_HashString_create("file");
}
