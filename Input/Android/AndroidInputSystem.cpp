#include "../InputSystem.h"
#include "AndroidInputSystem.h"

#include "../Keyboard.h"
#include "../Pointer.h"
#include "../Pad.h"
#include "../Joystick.h"

#include "../../Events/EventSystem.h"
#include "../../Events/Android/AndroidEvents.h"

#include <android/keycodes.h>

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
	if (event->getEventType() == AndroidEvents::Input::Keyboard::KeyDown)
		mKeyboard->setKey(convertKey(reinterpret_cast<AndroidEvents::Input::Keyboard::KeyDownEvent*>(event)->getKey()), true);
	else if (event->getEventType() == AndroidEvents::Input::Keyboard::KeyUp)
		mKeyboard->setKey(convertKey(reinterpret_cast<AndroidEvents::Input::Keyboard::KeyUpEvent*>(event)->getKey()), false);
	else if (event->getEventType() == AndroidEvents::Input::Touch::Moved) {
		mPointer->setAxis(Controller::Axis::X, reinterpret_cast<AndroidEvents::Input::Touch::MovedEvent*>(event)->getX());
		mPointer->setAxis(Controller::Axis::Y, reinterpret_cast<AndroidEvents::Input::Touch::MovedEvent*>(event)->getY());
	}
	else if (event->getEventType() == AndroidEvents::Input::Touch::TouchDown) {
		mPointer->setButton(0, 1.0F);
	}
	else if (event->getEventType() == AndroidEvents::Input::Touch::TouchUp)
		mPointer->setButton(0, 0.0F);
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
		mEventSystem->registerObserver(AndroidEvents::Input::Keyboard::KeyDown, this);
		mEventSystem->registerObserver(AndroidEvents::Input::Keyboard::KeyUp, this);

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
		mEventSystem->registerObserver(AndroidEvents::Input::Touch::TouchDown, this);
		mEventSystem->registerObserver(AndroidEvents::Input::Touch::TouchUp, this);
		mEventSystem->registerObserver(AndroidEvents::Input::Touch::Moved, this);

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
		mEventSystem->deregisterObserver(AndroidEvents::Input::Keyboard::KeyDown, this);
		mEventSystem->deregisterObserver(AndroidEvents::Input::Keyboard::KeyUp, this);
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
		mEventSystem->deregisterObserver(AndroidEvents::Input::Touch::TouchDown, this);
		mEventSystem->deregisterObserver(AndroidEvents::Input::Touch::TouchUp, this);
		mEventSystem->deregisterObserver(AndroidEvents::Input::Touch::Moved, this);
		delete mPointer;
		mPointer = 0;
	}

	// Should error here.. somehow we've gotten a pointer controller that doesn't belong to us!
}

Controller::KeyType InputSystem::convertKey(int androidKey)
{
	// What an arse...
	switch (androidKey) {
		case AKEYCODE_Q:				return Controller::KEY_Q;
		case AKEYCODE_W:				return Controller::KEY_W;
		case AKEYCODE_E:				return Controller::KEY_E;
		case AKEYCODE_R:				return Controller::KEY_R;
		case AKEYCODE_T:				return Controller::KEY_T;
		case AKEYCODE_Y:				return Controller::KEY_Y;
		case AKEYCODE_U:				return Controller::KEY_U;
		case AKEYCODE_I:				return Controller::KEY_I;
		case AKEYCODE_O:				return Controller::KEY_O;
		case AKEYCODE_P:				return Controller::KEY_P;
		case AKEYCODE_LEFT_BRACKET:		return Controller::KEY_LEFT_SQUARE_BRACKET;
		case AKEYCODE_RIGHT_BRACKET:	return Controller::KEY_RIGHT_SQUARE_BRACKET;
		case AKEYCODE_A:				return Controller::KEY_A;
		case AKEYCODE_S:				return Controller::KEY_S;
		case AKEYCODE_D:				return Controller::KEY_D;
		case AKEYCODE_F:				return Controller::KEY_F;
		case AKEYCODE_G:				return Controller::KEY_G;
		case AKEYCODE_H:				return Controller::KEY_H;
		case AKEYCODE_J:				return Controller::KEY_J;
		case AKEYCODE_K:				return Controller::KEY_K;
		case AKEYCODE_L:				return Controller::KEY_L;
		case AKEYCODE_SEMICOLON:		return Controller::KEY_SEMICOLON;
		case AKEYCODE_APOSTROPHE:		return Controller::KEY_APOSTROPHE;
		case AKEYCODE_POUND:			return Controller::KEY_TILDE;
		case AKEYCODE_SLASH:			return Controller::KEY_FORWARDSLASH;
		case AKEYCODE_Z:				return Controller::KEY_Z;
		case AKEYCODE_X:				return Controller::KEY_X;
		case AKEYCODE_C:				return Controller::KEY_C;
		case AKEYCODE_V:				return Controller::KEY_V;
		case AKEYCODE_B:				return Controller::KEY_B;
		case AKEYCODE_N:				return Controller::KEY_N;
		case AKEYCODE_M:				return Controller::KEY_M;
		case AKEYCODE_COMMA:			return Controller::KEY_COMMA;
		case AKEYCODE_PERIOD:			return Controller::KEY_PERIOD;
		case AKEYCODE_BACKSLASH:		return Controller::KEY_BACKSLASH;
		case AKEYCODE_SPACE:			return Controller::KEY_SPACE;
		case AKEYCODE_ENTER:			return Controller::KEY_RETURN;
		case AKEYCODE_DPAD_LEFT:		return Controller::KEY_ARROW_LEFT;
		case AKEYCODE_DPAD_RIGHT:		return Controller::KEY_ARROW_RIGHT;
		case AKEYCODE_DPAD_UP:			return Controller::KEY_ARROW_UP;
		case AKEYCODE_DPAD_DOWN:		return Controller::KEY_ARROW_DOWN;
		case AKEYCODE_BACK:				return Controller::KEY_ESCAPE;
		default:
			return Controller::KEY_SPACE;
	}
}

