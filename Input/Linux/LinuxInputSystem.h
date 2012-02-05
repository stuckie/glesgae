#ifndef _LINUX_INPUT_SYSTEM_H_
#define _LINUX_INPUT_SYSTEM_H_

#include <list>

#include "../../Resources/Resource.h"
#include "../../Events/EventObserver.h"
#include "../ControllerTypes.h"

#include <X11/Xlib.h>

namespace GLESGAE
{
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
			std::list<Resource<Controller::JoystickController> > mJoysticks;
			std::list<Resource<Controller::PadController> > mPads;

			Resource<EventSystem> mEventSystem;
	};
}

#endif
