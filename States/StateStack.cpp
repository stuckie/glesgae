#include "StateStack.h"

using namespace GLESGAE;

StateStack::StateStack()
: mLastState()
, mStack()
{
}

StateStack::StateStack(const StateStack& stateStack)
: mLastState(stateStack.mLastState)
, mStack(stateStack.mStack)
{
}

StateStack& StateStack::operator=(const StateStack& stateStack)
{
	if (this != &stateStack) {
		mLastState = stateStack.mLastState;
		for (std::vector<State*>::iterator itr(mStack.begin()); itr < mStack.end(); ++itr)
			delete *itr;
		mStack = stateStack.mStack;
	}
	
	return *this;
}

void StateStack::pop()
{
	if (false == mStack.empty()) {
		mLastState = *(mStack.end() - 1U);
		mStack.pop_back();
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
	
	if (mLastState != 0) {
		delete mLastState;
		mLastState = 0;
	}
	
	return status;
}

