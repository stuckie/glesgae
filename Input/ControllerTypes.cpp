#include "ControllerTypes.h"

using namespace GLESGAE;

Controller::Type Controller::Pointer = 	HashString("Controller::Pointer");
Controller::Type Controller::Keyboard = HashString("Controller::Keyboard");
Controller::Type Controller::Pad = 		HashString("Controller::Pad");
Controller::Type Controller::Joystick = HashString("Controller::Joystick");

Controller::Axes Controller::Axis::X = 0U;
Controller::Axes Controller::Axis::Y = 1U;

