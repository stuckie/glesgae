#include "../InputSystem.h"
#include "LinuxInputSystem.h"

#include "../Keyboard.h"
#include "../Pointer.h"
#include "../Pad.h"
#include "../Joystick.h"

#include "../../Events/EventSystem.h"
#include "../../Events/X11/X11Events.h"

#include <X11/keysym.h>

using namespace GLESGAE;

InputSystem::InputSystem(EventSystem* const eventSystem)
: CommonInputSystem()
, mKeyboard()
, mPointer()
, mJoysticks()
, mPads()
, mEventSystem(eventSystem)
{

}

InputSystem::~InputSystem()
{
}

void InputSystem::update()
{
	// Use X11 to deal with Joystick/Pad madness.. Keyboard and Pointer come through as Events.
}

void InputSystem::receiveEvent(Event* const event)
{
	if (event->getEventType() == X11Events::Input::Keyboard::KeyDown)
		mKeyboard->setKey(convertKey(reinterpret_cast<X11Events::Input::Keyboard::KeyDownEvent*>(event)->getKey()), true);
	else if (event->getEventType() == X11Events::Input::Keyboard::KeyUp)
		mKeyboard->setKey(convertKey(reinterpret_cast<X11Events::Input::Keyboard::KeyUpEvent*>(event)->getKey()), false);
	else if (event->getEventType() == X11Events::Input::Mouse::Moved) {
		mPointer->setAxis(Controller::Axis::X, reinterpret_cast<X11Events::Input::Mouse::MovedEvent*>(event)->getX());
		mPointer->setAxis(Controller::Axis::Y, reinterpret_cast<X11Events::Input::Mouse::MovedEvent*>(event)->getY());
	}
	else if (event->getEventType() == X11Events::Input::Mouse::ButtonDown)
		mPointer->setButton(reinterpret_cast<X11Events::Input::Mouse::ButtonDownEvent*>(event)->getButton(), 1.0F);
	else if (event->getEventType() == X11Events::Input::Mouse::ButtonUp)
		mPointer->setButton(reinterpret_cast<X11Events::Input::Mouse::ButtonUpEvent*>(event)->getButton(), 0.0F);
}

unsigned int InputSystem::getNumberOfKeyboards() const
{
	return 1U;
}

unsigned int InputSystem::getNumberOfJoysticks() const
{
	return mJoysticks.size();
}

unsigned int InputSystem::getNumberOfPads() const
{
	return mPads.size();
}

unsigned int InputSystem::getNumberOfPointers() const
{
	return 1U;
}

Controller::KeyboardController* InputSystem::newKeyboard()
{
	if (mKeyboard == 0) {
		mKeyboard = new Controller::KeyboardController(0U);
		mEventSystem->registerObserver(X11Events::Input::Keyboard::KeyDown, this);
		mEventSystem->registerObserver(X11Events::Input::Keyboard::KeyUp, this);

		return mKeyboard;
	}

	return 0;
}

Controller::JoystickController* InputSystem::newJoystick()
{
	// TODO: support joysticks - including pads with analog sticks
	return 0;
}

Controller::PadController* InputSystem::newPad()
{
	// TODO: support pads - purely digital pads without joysticks
	return 0;
}

Controller::PointerController* InputSystem::newPointer()
{
	if (mPointer == 0) {
		mPointer = new Controller::PointerController(0U, 5U);
		mEventSystem->registerObserver(X11Events::Input::Mouse::ButtonDown, this);
		mEventSystem->registerObserver(X11Events::Input::Mouse::ButtonUp, this);
		mEventSystem->registerObserver(X11Events::Input::Mouse::Moved, this);

		return mPointer;
	}

	return 0;
}

Controller::KeyboardController* InputSystem::getKeyboard(const Controller::Id id)
{
	if (0 == id)
		return mKeyboard;
	else
		return 0;
}

Controller::JoystickController* InputSystem::getJoystick(const Controller::Id /*joystickId*/)
{
	// TODO: support joysticks
	return 0;
}

Controller::PointerController* InputSystem::getPointer(const Controller::Id id)
{
	if (0 == id)
		return mPointer;
	else
		return 0;
}

Controller::PadController* InputSystem::getPad(const Controller::Id /*padId*/)
{
	// TODO: support pads
	return 0;
}

void InputSystem::destroyKeyboard(Controller::KeyboardController* const keyboard)
{
	if (mKeyboard == keyboard) {
		mEventSystem->deregisterObserver(X11Events::Input::Keyboard::KeyDown, this);
		mEventSystem->deregisterObserver(X11Events::Input::Keyboard::KeyUp, this);
		delete mKeyboard;
		mKeyboard = 0;
	}

	// Should error here.. somehow we've gotten a keyboard controller that doesn't belong to us!
}

void InputSystem::destroyJoystick(Controller::JoystickController* const /*joystickController*/)
{
	// Run through list and check we actually own this Joystick, then delete.
}

void InputSystem::destroyPad(Controller::PadController* const /*padController*/)
{
	// Run through list and check we actually own this Pad, then delete.
}

void InputSystem::destroyPointer(Controller::PointerController* const pointer)
{
	if (mPointer == pointer) {
		mEventSystem->deregisterObserver(X11Events::Input::Mouse::ButtonDown, this);
		mEventSystem->deregisterObserver(X11Events::Input::Mouse::ButtonUp, this);
		mEventSystem->deregisterObserver(X11Events::Input::Mouse::Moved, this);
		delete mPointer;
		mPointer = 0;
	}

	// Should error here.. somehow we've gotten a pointer controller that doesn't belong to us!
}

Controller::KeyType InputSystem::convertKey(KeySym x11Key)
{
	// What an arse...
	switch (x11Key) {
		case XK_q: case XK_Q:	return Controller::KEY_Q;
		case XK_w: case XK_W:	return Controller::KEY_W;
		case XK_e: case XK_E:	return Controller::KEY_E;
		case XK_r: case XK_R:	return Controller::KEY_R;
		case XK_t: case XK_T:	return Controller::KEY_T;
		case XK_y: case XK_Y:	return Controller::KEY_Y;
		case XK_u: case XK_U:	return Controller::KEY_U;
		case XK_i: case XK_I:	return Controller::KEY_I;
		case XK_o: case XK_O:	return Controller::KEY_O;
		case XK_p: case XK_P:	return Controller::KEY_P;
		case XK_bracketleft:	return Controller::KEY_LEFT_SQUARE_BRACKET;
		case XK_bracketright:	return Controller::KEY_RIGHT_SQUARE_BRACKET;
		case XK_a: case XK_A:	return Controller::KEY_A;
		case XK_s: case XK_S:	return Controller::KEY_S;
		case XK_d: case XK_D:	return Controller::KEY_D;
		case XK_f: case XK_F:	return Controller::KEY_F;
		case XK_g: case XK_G:	return Controller::KEY_G;
		case XK_h: case XK_H:	return Controller::KEY_H;
		case XK_j: case XK_J:	return Controller::KEY_J;
		case XK_k: case XK_K:	return Controller::KEY_K;
		case XK_l: case XK_L:	return Controller::KEY_L;
		case XK_semicolon:		return Controller::KEY_SEMICOLON;
		case XK_quotedbl:		return Controller::KEY_APOSTROPHE;
		case XK_numbersign:		return Controller::KEY_TILDE;
		case XK_slash:			return Controller::KEY_FORWARDSLASH;
		case XK_z: case XK_Z:	return Controller::KEY_Z;
		case XK_x: case XK_X:	return Controller::KEY_X;
		case XK_c: case XK_C:	return Controller::KEY_C;
		case XK_v: case XK_V:	return Controller::KEY_V;
		case XK_b: case XK_B:	return Controller::KEY_B;
		case XK_n: case XK_N:	return Controller::KEY_N;
		case XK_m: case XK_M:	return Controller::KEY_M;
		case XK_comma:			return Controller::KEY_COMMA;
		case XK_period:			return Controller::KEY_PERIOD;
		case XK_backslash:		return Controller::KEY_BACKSLASH;
		case XK_space:			return Controller::KEY_SPACE;
		case XK_Return:			return Controller::KEY_RETURN;
		case XK_Left:			return Controller::KEY_ARROW_LEFT;
		case XK_Right:			return Controller::KEY_ARROW_RIGHT;
		case XK_Up:				return Controller::KEY_ARROW_UP;
		case XK_Down:			return Controller::KEY_ARROW_DOWN;
		case XK_Escape:			return Controller::KEY_ESCAPE;
		default:
			return Controller::KEY_SPACE;
	}
}
