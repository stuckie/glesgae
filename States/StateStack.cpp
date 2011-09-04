#include "StateStack.h"

using namespace GLESGAE;

StateStack::StateStack()
: mStack()
{
}

void StateStack::pop()
{
	if (false == mStack.empty()) {
		mStack.pop_back();
		delete *(mStack.end());
	}
}

State* StateStack::get()
{
	if (false == mStack.empty())
		return mStack[mStack.size() - 1U];
	else
		return 0;
}

bool StateStack::update(const float delta)
{
	bool status(false);
	
	if (false == mStack.empty())
		status = mStack[mStack.size() - 1U]->update(delta);
	
	return status;
}

