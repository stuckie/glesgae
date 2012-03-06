#ifndef _JAVA_SCRIPT_TIMED_FUNCTION_H_
#define _JAVA_SCRIPT_TIMED_FUNCTION_H_

#include <JavaScriptCore/JavaScript.h>
#include "../../Time/Timer.h"

namespace GLESGAE
{

class JavaScriptTimedFunction
{
	public:
		JavaScriptTimedFunction(const float callbackTime, JSObjectRef function, const bool recurring);
		JavaScriptTimedFunction(const JavaScriptTimedFunction& rhs);
		JavaScriptTimedFunction& operator=(const JavaScriptTimedFunction& rhs);
		
		/// Update the timer, and check when we're needed to be called.
		/// Returns false if no longer needs to be called.
		bool update();
	
	private:
		Timer mTimer;
		bool mRecurring;
		float mCallbackTime;
		JSObjectRef mFunction;
};

}

#endif
