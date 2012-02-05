#include "StateStack.h"

using namespace GLESGAE;

StateStack::StateStack()
: mLastState()
, mStack()
{
}

void StateStack::pop()
{
	if (false == mStack.empty()) {
		mLastState = *(mStack.end() - 1U);
		mStack.pop_back();
	}
}

Resource<State> StateStack::get()
{
	if (false == mStack.empty())
		return mStack[mStack.size() - 1U];
	else
		return Resource<State>();
}

bool StateStack::update(const float delta)
{
	bool status(false);
	
	if (false == mStack.empty())
		status = mStack[mStack.size() - 1U]->update(delta);
	
	if (mLastState != 0)
		mLastState = Resource<State>();
	
	return status;
}

