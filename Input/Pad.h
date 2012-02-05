#ifndef _PAD_H_
#define _PAD_H_

#include "Controller.h"
#include "ControllerTypes.h"

#include <vector>

namespace GLESGAE
{
	class InputSystem;
	namespace Controller
	{
		class PadController : public CommonController
		{
			friend class GLESGAE::InputSystem;
			public:
				PadController(const Controller::Id controllerId, const int buttons)
				: CommonController(Pad, controllerId)
				, mButtons(buttons)
				{
				}
				
				/// Get the value of the specified button
				float getButton(const Button button) const
				{
					// TODO: actual error checking
					return mButtons[button];
				}
				
				/// Get amount of buttons
				unsigned int getNumButtons() const { return mButtons.size(); }
								
			protected:
				/// Set Button data
				void setButton(const Button button, const float data)
				{
					// TODO: actual error checking
					mButtons[button] = data;
				}
				
			private:
				std::vector<float> mButtons;
		};
	}
}

#endif
