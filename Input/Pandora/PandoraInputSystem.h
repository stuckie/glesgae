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
			InputSystem(EventSystem* const eventSystem);
			~InputSystem();

			/// Update the Input System
			void update();

			/// Receive an Event
			void receiveEvent(Event* const event);

			/// Retreive number of Active Keyboards.
			unsigned int getNumberOfKeyboards() const;

			/// Retreive number of Active Joysticks.
			unsigned int getNumberOfJoysticks() const;

			/// Retreive number of Active Pads.
			unsigned int getNumberOfPads() const;

			/// Retreive number of Active Pointers.
			unsigned int getNumberOfPointers() const;

			/// Create new Keyboard - will return NULL if no more available.
			Controller::KeyboardController* newKeyboard();

			/// Create new Joystick - will return NULL if no more available.
			Controller::JoystickController* newJoystick();

			/// Create new Pad - will return NULL if no more available.
			Controller::PadController* newPad();

			/// Create new Pointer - will return NULL if no more available.
			Controller::PointerController* newPointer();

			/// Grab another instance of the specified Keyboard - returns NULL if not created.
			Controller::KeyboardController* getKeyboard(const Controller::Id id);

			/// Grab another instance of the specified Joystick - returns NULL if not created.
			Controller::JoystickController* getJoystick(const Controller::Id id);

			/// Grab another instance of the specified Pointer - returns NULL if not created.
			Controller::PointerController* getPointer(const Controller::Id id);

			/// Grab another instance of the specified Pad - returns NULL if not created.
			Controller::PadController* getPad(const Controller::Id id);

			/// Destroy a Keyboard.
			void destroyKeyboard(Controller::KeyboardController* const keyboard);

			/// Destroy a Joystick.
			void destroyJoystick(Controller::JoystickController* const joystick);

			/// Destroy a Pad.
			void destroyPad(Controller::PadController* const pad);

			/// Destroy a Pointer.
			void destroyPointer(Controller::PointerController* const pointer);

		protected:
			Controller::KeyType convertKey(KeySym x11Key);

		private:
			// No Copying
			InputSystem(const InputSystem&);
			InputSystem& operator=(const InputSystem&);
			
			Controller::KeyboardController* mKeyboard;
			Controller::PointerController* mPointer;
			std::vector<Controller::JoystickController*> mJoysticks;
			std::vector<Controller::PadController*> mPads;

			EventSystem* mEventSystem;
	};
}

#endif
