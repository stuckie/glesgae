#ifndef _EVENT_TYPES_H_
#define _EVENT_TYPES_H_

#include "../Utils/HashString.h"

namespace GLESGAE
{
	typedef const HashString EventType;
	
	namespace SystemEvents
	{
		namespace App
		{
			extern EventType Started;
			extern EventType Paused;
			extern EventType Resumed;
			extern EventType Destroyed;
		}
		
		namespace Window
		{
			extern EventType Opened;
			extern EventType Resized;
			extern EventType Closed;
		}
	}
}

#endif
