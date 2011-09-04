#ifndef _EVENT_TYPES_H_
#define _EVENT_TYPES_H_

namespace GLESGAE
{
	typedef unsigned int EventType;
	
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
