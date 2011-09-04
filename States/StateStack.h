#ifndef _STATE_STACK_H_
#define _STATE_STACK_H_

#include "../Resources/Resource.h"
#include "State.h"

#include <vector>

namespace GLESGAE
{
	class StateStack
	{
		public:
			StateStack();
			
			/// Push a new State onto the Stack - keeping the other ones in place beneath.
			template <typename T_State> void push();
			
			/// Replaces the current State with this State.
			template <typename T_State>	void replace();
			
			/// Pops the current State off the stack, and resumes the one below.
			void pop();
			
			/// Retrieves the current State.
			State* get();
			
			/// Update the current State.
			bool update(const float delta);
			
		private:
			std::vector<State*> mStack;
	};
	
	template <typename T_State>
	void StateStack::push()
	{
		mStack.push_back(new T_State);
	}

	template <typename T_State>
	void StateStack::replace()
	{
		pop();
		push<T_State>();
	}
}

#endif

