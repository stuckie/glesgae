#ifndef _CONTROLLER_TYPES_H_
#define _CONTROLLER_TYPES_H_

#include "../Utils/HashString.h"

namespace GLESGAE
{
	namespace Controller
	{
		typedef unsigned int Id;
		typedef const HashString Type;
		typedef unsigned int KeyType;
		typedef unsigned int Axes;
		typedef unsigned int Button;
		
		extern Type Pointer;
		extern Type Keyboard;
		extern Type Pad;
		extern Type Joystick;
		
		namespace Axis
		{
			extern Axes X;
			extern Axes Y;
		}
	}
}

#endif
