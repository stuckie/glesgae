#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "ControllerTypes.h"

namespace GLESGAE
{
	class CommonController
	{
		public:
			CommonController(const Controller::Type& controllerType, const Controller::Id controllerId)
			: mControllerType(controllerType)
			, mControllerId(controllerId)
			{
				
			}
			
			virtual ~CommonController() {}
			
			/// Return the type of this Controller
			Controller::Type getControllerType() const { return mControllerType; }
			
			/// Return the id of this Controller
			Controller::Id getControllerId() const { return mControllerId; }
			
		private:
			Controller::Type mControllerType;
			Controller::Id mControllerId;
	};
}

#endif
