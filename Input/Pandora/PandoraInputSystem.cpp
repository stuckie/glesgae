#include <vector>

#include "../InputSystem.h"
#include "PandoraInputSystem.h"

#include "../Keyboard.h"
#include "../Pointer.h"
#include "../Pad.h"
#include "../Joystick.h"

#include "../../Events/EventSystem.h"
#include "../../Events/X11/X11Events.h"

#include "pnd_io_evdev.h"

#include <X11/keysym.h>

using namespace GLESGAE;

Controller::Button Controller::Pandora::Up		= 0U;
Controller::Button Controller::Pandora::Down		= 1U;
Controller::Button Controller::Pandora::Left		= 2U;
Controller::Button Controller::Pandora::Right		= 3U;
Controller::Button Controller::Pandora::Start		= 4U;
Controller::Button Controller::Pandora::Select		= 5U;
Controller::Button Controller::Pandora::Pandora		= 6U;
Controller::Button Controller::Pandora::Y		= 7U;
Controller::Button Controller::Pandora::B		= 8U;
Controller::Button Controller::Pandora::X		= 9U;
Controller::Button Controller::Pandora::A		= 10U;
Controller::Button Controller::Pandora::L1		= 11U;
Controller::Button Controller::Pandora::R1		= 12U;
Controller::Button Controller::Pandora::L2		= 13U;
Controller::Button Controller::Pandora::R2		= 14U;

Controller::Id Controller::Pandora::LeftNub 		= 0U;
Controller::Id Controller::Pandora::RightNub		= 1U;

Controller::Id Controller::Pandora::Buttons		= 0U;

InputSystem::InputSystem(const Resource<EventSystem>& eventSystem)
: CommonInputSystem()
, mKeyboard(0)
, mPointer(0)
, mJoysticks()
, mPads()
, mEventSystem(eventSystem)
{
	mJoysticks.push_back(Resource<Controller::JoystickController>(new Controller::JoystickController(Controller::Pandora::LeftNub, 2U, 0U))); // ID, 2 Axes, 0 Buttons
	mJoysticks.push_back(Resource<Controller::JoystickController>(new Controller::JoystickController(Controller::Pandora::RightNub, 2U, 0U))); // ID, 2 Axes, 0 Buttons

	mPads.push_back(Resource<Controller::PadController>(new Controller::PadController(Controller::Pandora::Buttons, 15U))); // 15 Buttons - Up/Down/Left/Right - Start/Select/Pandora - Y/B/X/A - L1/R1/L2/R2 ( L2/R2 being optional, of course )

	pnd_evdev_open(pnd_evdev_dpads);
	pnd_evdev_open(pnd_evdev_nub1);
	pnd_evdev_open(pnd_evdev_nub2);
}

InputSystem::~InputSystem()
{
	mJoysticks.clear();
	mPads.clear();

	pnd_evdev_close(pnd_evdev_dpads);
	pnd_evdev_close(pnd_evdev_nub1);
	pnd_evdev_close(pnd_evdev_nub2);
}

void InputSystem::update()
{
	// Use libPND to update Nubs and Buttons... keyboard and pointer come through as events.
	pnd_evdev_catchup(0);

	pnd_nubstate_t nubState;

	// Left Nub
	if (pnd_evdev_nub_state(pnd_evdev_nub1, &nubState) > 0) {
		mJoysticks[Controller::Pandora::LeftNub]->setAxis(Controller::Axis::X, static_cast<float>(nubState.x));
		mJoysticks[Controller::Pandora::LeftNub]->setAxis(Controller::Axis::Y, static_cast<float>(nubState.y));
	}

	// Right Nub
	if (pnd_evdev_nub_state(pnd_evdev_nub2, &nubState) > 0) {
		mJoysticks[Controller::Pandora::RightNub]->setAxis(Controller::Axis::X, static_cast<float>(nubState.x));
		mJoysticks[Controller::Pandora::RightNub]->setAxis(Controller::Axis::Y, static_cast<float>(nubState.y));
	}

	// Buttons
	Controller::Button buttonState(pnd_evdev_dpad_state(pnd_evdev_dpads));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::Left, (buttonState & pnd_evdev_left));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::Right, (buttonState & pnd_evdev_right));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::Up, (buttonState & pnd_evdev_up));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::Down, (buttonState & pnd_evdev_down));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::X, (buttonState & pnd_evdev_x));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::Y, (buttonState & pnd_evdev_y));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::A, (buttonState & pnd_evdev_a));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::B, (buttonState & pnd_evdev_b));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::L1, (buttonState & pnd_evdev_ltrigger));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::R1, (buttonState & pnd_evdev_rtrigger));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::Start, (buttonState & pnd_evdev_start));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::Select, (buttonState & pnd_evdev_select));
	mPads[Controller::Pandora::Buttons]->setButton(Controller::Pandora::Pandora, (buttonState & pnd_evdev_pandora));
}

void InputSystem::receiveEvent(const Resource<Event>& event)
{
	if (event->getEventType() == X11Events::Input::Keyboard::KeyDown)
		mKeyboard->setKey(convertKey(event.recast<X11Events::Input::Keyboard::KeyDownEvent>()->getKey()), true);
	else if (event->getEventType() == X11Events::Input::Keyboard::KeyUp)
		mKeyboard->setKey(convertKey(event.recast<X11Events::Input::Keyboard::KeyUpEvent>()->getKey()), false);
	else if (event->getEventType() == X11Events::Input::Mouse::Moved) {
		mPointer->setAxis(Controller::Axis::X, event.recast<X11Events::Input::Mouse::MovedEvent>()->getX());
		mPointer->setAxis(Controller::Axis::Y, event.recast<X11Events::Input::Mouse::MovedEvent>()->getY());
	}
	else if (event->getEventType() == X11Events::Input::Mouse::ButtonDown)
		mPointer->setButton(event.recast<X11Events::Input::Mouse::ButtonDownEvent>()->getButton(), 1.0F);
	else if (event->getEventType() == X11Events::Input::Mouse::ButtonUp)
		mPointer->setButton(event.recast<X11Events::Input::Mouse::ButtonUpEvent>()->getButton(), 0.0F);
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

Resource<Controller::KeyboardController> InputSystem::newKeyboard()
{
	if (mKeyboard == 0) {
		mKeyboard = Resource<Controller::KeyboardController>(new Controller::KeyboardController(0U));
		mEventSystem->registerObserver(X11Events::Input::Keyboard::KeyDown, this);
		mEventSystem->registerObserver(X11Events::Input::Keyboard::KeyUp, this);

		return mKeyboard;
	}

	return Resource<Controller::KeyboardController>(0);
}

Resource<Controller::JoystickController> InputSystem::newJoystick()
{
	// TODO: support joysticks - including pads with analog sticks
	return Resource<Controller::JoystickController>(0);
}

Resource<Controller::PadController> InputSystem::newPad()
{
	// TODO: support pads - purely digital pads without joysticks
	return Resource<Controller::PadController>(0);
}

Resource<Controller::PointerController> InputSystem::newPointer()
{
	if (mPointer == 0) {
		mPointer = Resource<Controller::PointerController>(new Controller::PointerController(0U, 5U)); // 5 buttons, left, middle, right, scroll up, scroll down
		mEventSystem->registerObserver(X11Events::Input::Mouse::ButtonDown, this);
		mEventSystem->registerObserver(X11Events::Input::Mouse::ButtonUp, this);
		mEventSystem->registerObserver(X11Events::Input::Mouse::Moved, this);

		return mPointer;
	}

	return Resource<Controller::PointerController>(0);
}

Resource<Controller::KeyboardController> InputSystem::getKeyboard(const Controller::Id id)
{
	if (0 == id)
		return mKeyboard;
	else
		return Resource<Controller::KeyboardController>(0);
}

Resource<Controller::JoystickController> InputSystem::getJoystick(const Controller::Id id)
{
	// TODO: support joysticks
	if (id < Controller::Pandora::RightNub + 1U) // hacky check
		return mJoysticks[id];
	else
		return Resource<Controller::JoystickController>(0);
}

Resource<Controller::PointerController> InputSystem::getPointer(const Controller::Id id)
{
	if (0 == id)
		return mPointer;
	else
		return Resource<Controller::PointerController>(0);
}

Resource<Controller::PadController> InputSystem::getPad(const Controller::Id id)
{
	// TODO: support pads
	if (id < Controller::Pandora::Buttons + 1U) // hacky check
		return mPads[id];
	else
		return Resource<Controller::PadController>(0);
}

void InputSystem::destroyKeyboard(const Resource<Controller::KeyboardController>& keyboard)
{
	if (mKeyboard == keyboard) {
		mEventSystem->deregisterObserver(X11Events::Input::Keyboard::KeyDown, this);
		mEventSystem->deregisterObserver(X11Events::Input::Keyboard::KeyUp, this);
		mKeyboard = Resource<Controller::KeyboardController>(0);

		return;
	}

	// Should error here.. somehow we've gotten a keyboard controller that doesn't belong to us!
}

void InputSystem::destroyJoystick(const Resource<Controller::JoystickController>& /*joystick*/)
{
	// Run through list and check we actually own this Joystick, then delete.
}

void InputSystem::destroyPad(const Resource<Controller::PadController>& /*pad*/)
{
	// Run through list and check we actually own this Pad, then delete.
}

void InputSystem::destroyPointer(const Resource<Controller::PointerController>& pointer)
{
	if (mPointer == pointer) {
		mEventSystem->deregisterObserver(X11Events::Input::Mouse::ButtonDown, this);
		mEventSystem->deregisterObserver(X11Events::Input::Mouse::ButtonUp, this);
		mEventSystem->deregisterObserver(X11Events::Input::Mouse::Moved, this);
		mPointer = Resource<Controller::PointerController>(0);

		return;
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
