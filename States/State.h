#ifndef _STATE_H_
#define _STATE_H_

#include "../Utils/HashString.h"

namespace GLESGAE
{
	namespace States
	{
		typedef HashString Id;
	}
	
	class State
	{
		public:
			virtual ~State() {}
			
			/// Grab the Id of this state
			States::Id getId() const { return mId; }
			
			/// Single Update Function. Must be overloaded. Return true if successful update.
			virtual bool update(const float delta) = 0;
			
		protected:
			/// Private Constructor to force overloading
			State(const States::Id id) : mId(id) {}
			
		private:
			States::Id mId;
	};
}

#endif

