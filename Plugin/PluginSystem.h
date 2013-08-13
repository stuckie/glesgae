#ifndef _PLUGIN_SYSTEM_H_
#define _PLUGIN_SYSTEM_H_

#include "../Utils/HashString.h"

namespace GLESGAE
{
	class PluginSystem
	{
		public:
			virtual ~PluginSystem() {}

			// Return the name of this System to find it on the Application singleton.
			virtual HashString getName() const = 0;
	};
}

#endif
