#ifndef _BASE_RESOURCE_BANK_H_
#define _BASE_RESOURCE_BANK_H_

#include "BaseResource.h"

namespace GLESGAE
{
	class BaseResourceBank
	{
		friend class BaseResource;
		friend class ResourceManager;
		
		public:
			virtual ~BaseResourceBank() {} 
			
			/// Get the Type of this Resource Bank
			Resources::Type getType() const { return mType; }
			
			/// Get the If of this Resource Bank
			Resources::Id getId() const { return mId; }
			
			/// Create a new resource group.
			virtual Resources::Group newGroup() = 0;
			
			/// Remove Group
			virtual void removeGroup(const Resources::Group groupId) = 0;
			
			
		protected:
			/// Private constructor as this is a derived class only
			BaseResourceBank(const Resources::Id id, const Resources::Type type)
			: mId(id)
			, mType(type)
			{
			
			}
			
		private:
			// No Copying Allowed
			BaseResourceBank(const BaseResourceBank&);
			BaseResourceBank& operator=(const BaseResourceBank&);
			
			Resources::Id mId;
			Resources::Type mType;
	};

}

#endif
