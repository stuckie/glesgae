#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "Controller.h"
#include "ControllerTypes.h"

#include <vector>

namespace GLESGAE
{
	class InputSystem;
	namespace Controller
	{		
		extern KeyType KEY_A;
		extern KeyType KEY_B;
		extern KeyType KEY_C;
		extern KeyType KEY_D;
		extern KeyType KEY_E;
		extern KeyType KEY_F;
		extern KeyType KEY_G;
		extern KeyType KEY_H;
		extern KeyType KEY_I;
		extern KeyType KEY_J;
		extern KeyType KEY_K;
		extern KeyType KEY_L;
		extern KeyType KEY_M;
		extern KeyType KEY_N;
		extern KeyType KEY_O;
		extern KeyType KEY_P;
		extern KeyType KEY_Q;
		extern KeyType KEY_R;
		extern KeyType KEY_S;
		extern KeyType KEY_T;
		extern KeyType KEY_U;
		extern KeyType KEY_V;
		extern KeyType KEY_W;
		extern KeyType KEY_X;
		extern KeyType KEY_Y;
		extern KeyType KEY_Z;
		
		extern KeyType KEY_0;
		extern KeyType KEY_1;
		extern KeyType KEY_2;
		extern KeyType KEY_3;
		extern KeyType KEY_4;
		extern KeyType KEY_5;
		extern KeyType KEY_6;
		extern KeyType KEY_7;
		extern KeyType KEY_8;
		extern KeyType KEY_9;
		
		extern KeyType KEY_F1;
		extern KeyType KEY_F2;
		extern KeyType KEY_F3;
		extern KeyType KEY_F4;
		extern KeyType KEY_F5;
		extern KeyType KEY_F6;
		extern KeyType KEY_F7;
		extern KeyType KEY_F8;
		extern KeyType KEY_F9;
		extern KeyType KEY_F10;
		extern KeyType KEY_F11;
		extern KeyType KEY_F12;
		
		extern KeyType KEY_LEFT_SHIFT;
		extern KeyType KEY_RIGHT_SHIFT;
		
		extern KeyType KEY_LEFT_CTRL;
		extern KeyType KEY_RIGHT_CTRL;
		
		extern KeyType KEY_LEFT_ALT;
		extern KeyType KEY_RIGHT_ALT;
		
		extern KeyType KEY_CAPS_LOCK;
		extern KeyType KEY_RETURN;
		extern KeyType KEY_TAB;
		extern KeyType KEY_BACKSPACE;
		extern KeyType KEY_ESCAPE;
		extern KeyType KEY_SPACE;
		
		extern KeyType KEY_BACKSLASH;
		extern KeyType KEY_FORWARDSLASH;
		extern KeyType KEY_COMMA;
		extern KeyType KEY_PERIOD;
		extern KeyType KEY_SEMICOLON;
		extern KeyType KEY_APOSTROPHE;
		extern KeyType KEY_LEFT_SQUARE_BRACKET;
		extern KeyType KEY_RIGHT_SQUARE_BRACKET;
		extern KeyType KEY_BACKTICK;
		extern KeyType KEY_MINUS;
		extern KeyType KEY_PLUS;
		extern KeyType KEY_TILDE;
		extern KeyType KEY_ASTERISK;
		
		extern KeyType KEY_ARROW_UP;
		extern KeyType KEY_ARROW_DOWN;
		extern KeyType KEY_ARROW_LEFT;
		extern KeyType KEY_ARROW_RIGHT;
		
		extern KeyType MAX_KEYS;
		
		class KeyboardController : public CommonController
		{
			friend class GLESGAE::InputSystem;
			public:
				KeyboardController(const Controller::Id controllerId)
				: CommonController(Keyboard, controllerId)
				, mKeys(MAX_KEYS)
				{
					
				}
				
				/// Get the value of the specified key
				bool getKey(const KeyType key) const
				{ 
					// TODO: actual error checking
					return mKeys[key];
				}
				
			protected:
				/// Set Key data
				void setKey(const KeyType key, const bool data)
				{
					// TODO: actual error checking
					mKeys[key] = data;
				}
				
			private:
				std::vector<bool> mKeys;
		};
	}
}

#endif
