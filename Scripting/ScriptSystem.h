#ifndef _SCRIPT_SYSTEM_H_
#define _SCRIPT_SYSTEM_H_

namespace GLESGAE
{

class ScriptSystem
{
	public:
		ScriptSystem() {};
		virtual ~ScriptSystem() {};
		
		/// Update the Script System
		virtual void update() = 0;
};

}

#endif
