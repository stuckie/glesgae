#ifndef _CONTROLLER_TYPES_H_
#define _CONTROLLER_TYPES_H_

namespace GLESGAE
{
	namespace Controller
	{
		typedef unsigned int Id;
		typedef unsigned int Type;
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
