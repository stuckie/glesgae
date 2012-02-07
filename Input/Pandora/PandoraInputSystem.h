#ifndef _PANDORA_INPUT_SYSTEM_H_
#define _PANDORA_INPUT_SYSTEM_H_

#include <vector>

#include "../ControllerTypes.h"
#include "../../Events/EventObserver.h"

#include <X11/Xlib.h>

namespace GLESGAE
{
	namespace Controller
	{
		namespace Pandora {
			extern Controller::Button Up;
			extern Controller::Button Down;
			extern Controller::Button Left;
			extern Controller::Button Right;
			extern Controller::Button Start;
			extern Controller::Button Select;
			extern Controller::Button Pandora;
			extern Controller::Button Y;
			extern Controller::Button B;
			extern Controller::Button X;
			extern Controller::Button A;
			extern Controller::Button L1;
			extern Controller::Button L2;
			extern Controller::Button R1;
			extern Controller::Button R2;

			extern Controller::Id LeftNub;
			extern Controller::Id RightNub;
			extern Controller::Id Buttons;
		}
	}

	class Event;
	class EventSystem;
	class InputSystem : public CommonInputSystem, public EventObserver
	{
		public:
			InputSystem(const Resource<EventSystem>& eventSystem);
			~InputSystem();

			/// Update the Input System
			void update();

			/// Receive an Event
			void receiveEvent(const Resource<Event>& event);

			/// Retreive number of Active Keyboards.
			unsigned int getNumberOfKeyboards() const;

			/// Retreive number of Active Joysticks.
			unsigned int getNumberOfJoysticks() const;

			/// Retreive number of Active Pads.
			unsigned int getNumberOfPads() const;

			/// Retreive number of Active Pointers.
			unsigned int getNumberOfPointers() const;

			/// Create new Keyboard - will return NULL if no more available.
			Resource<Controller::KeyboardController> newKeyboard();

			/// Create new Joystick - will return NULL if no more available.
			Resource<Controller::JoystickController> newJoystick();

			/// Create new Pad - will return NULL if no more available.
			Resource<Controller::PadController> newPad();

			/// Create new Pointer - will return NULL if no more available.
			Resource<Controller::PointerController> newPointer();

			/// Grab another instance of the specified Keyboard - returns NULL if not created.
			Resource<Controller::KeyboardController> getKeyboard(const Controller::Id id);

			/// Grab another instance of the specified Joystick - returns NULL if not created.
			Resource<Controller::JoystickController> getJoystick(const Controller::Id id);

			/// Grab another instance of the specified Pointer - returns NULL if not created.
			Resource<Controller::PointerController> getPointer(const Controller::Id id);

			/// Grab another instance of the specified Pad - returns NULL if not created.
			Resource<Controller::PadController> getPad(const Controller::Id id);

			/// Destroy a Keyboard.
			void destroyKeyboard(const Resource<Controller::KeyboardController>& keyboard);

			/// Destroy a Joystick.
			void destroyJoystick(const Resource<Controller::JoystickController>& joystick);

			/// Destroy a Pad.
			void destroyPad(const Resource<Controller::PadController>& pad);

			/// Destroy a Pointer.
			void destroyPointer(const Resource<Controller::PointerController>& pointer);

		protected:
			Controller::KeyType convertKey(KeySym x11Key);

		private:
			// No Copying
			InputSystem(const InputSystem&);
			InputSystem& operator=(const InputSystem&);
			
			Resource<Controller::KeyboardController> mKeyboard;
			Resource<Controller::PointerController> mPointer;
			std::vector<Resource<Controller::JoystickController> > mJoysticks;
			std::vector<Resource<Controller::PadController> > mPads;

			Resource<EventSystem> mEventSystem;
	};
}

#endif
