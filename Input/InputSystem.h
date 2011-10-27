#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include "ControllerTypes.h"
#include "../Resources/Resource.h"

namespace GLESGAE
{
	namespace Controller
	{
		class KeyboardController;
		class PointerController;
		class JoystickController;
		class PadController;
	}
	class CommonInputSystem
	{
		public:
			CommonInputSystem() {}
			virtual ~CommonInputSystem() {}
			
			/// Update the Input System
			virtual void update() = 0;
			
			/// Retreive number of Active Keyboards.
			virtual unsigned int getNumberOfKeyboards() const = 0;
			
			/// Retreive number of Active Joysticks.
			virtual unsigned int getNumberOfJoysticks() const = 0;
			
			/// Retreive number of Active Pads.
			virtual unsigned int getNumberOfPads() const = 0;
			
			/// Retreive number of Active Pointers.
			virtual unsigned int getNumberOfPointers() const = 0;
			
			/// Create new Keyboard - will return NULL if no more available.
			virtual Resource<Controller::KeyboardController> newKeyboard() = 0;
			
			/// Create new Joystick - will return NULL if no more available.
			virtual Resource<Controller::JoystickController> newJoystick() = 0;
			
			/// Create new Pad - will return NULL if no more available.
			virtual Resource<Controller::PadController> newPad() = 0;
			
			/// Create new Pointer - will return NULL if no more available.
			virtual Resource<Controller::PointerController> newPointer() = 0;
			
			/// Grab another instance of the specified Keyboard - returns NULL if not created.
			virtual Resource<Controller::KeyboardController> getKeyboard(const Controller::Id id) = 0;
			
			/// Grab another instance of the specified Joystick - returns NULL if not created.
			virtual Resource<Controller::JoystickController> getJoystick(const Controller::Id id) = 0;
			
			/// Grab another instance of the specified Pointer - returns NULL if not created.
			virtual Resource<Controller::PointerController> getPointer(const Controller::Id id) = 0;
			
			/// Grab another instance of the specified Pad - returns NULL if not created.
			virtual Resource<Controller::PadController> getPad(const Controller::Id id) = 0;
			
			/// Destroy a Keyboard.
			virtual void destroyKeyboard(const Resource<Controller::KeyboardController>& keyboard) = 0;
			
			/// Destroy a Joystick.
			virtual void destroyJoystick(const Resource<Controller::JoystickController>& joystick) = 0;
			
			/// Destroy a Pad.
			virtual void destroyPad(const Resource<Controller::PadController>& pad) = 0;
			
			/// Destroy a Pointer.
			virtual void destroyPointer(const Resource<Controller::PointerController>& pointer) = 0;
	};
}

#if defined(PANDORA)
	#include "Pandora/PandoraInputSystem.h"
#elif defined(LINUX)
	#include "Linux/LinuxInputSystem.h"
#endif

#endif
