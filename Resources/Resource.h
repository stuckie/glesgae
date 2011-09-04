#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "BaseResource.h"

namespace GLESGAE
{
	template <typename T_Resource> class ResourceBank;
	template <typename T_Resource> class Resource : public BaseResource
	{
		// Resource Bank is a friend to access purge.
		friend class ResourceBank<T_Resource>;
		public:
			/// Dummy Constructor for creation of empty Resources
			Resource() : BaseResource(Resources::INVALID, Resources::INVALID, Resources::INVALID), mResource(0) {}
			~Resource() { remove(); }
		
			/// Operator overload to return the actual resource.
			T_Resource* operator-> () { return mResource; }
			
			/// Const Operator overload.
			T_Resource* operator-> () const { return mResource; }
			
			/// Operator overload to return the actual resource.
			T_Resource& operator* () { return *mResource; }
			
			/// Const operator overload.
			const T_Resource& operator* () const { return *mResource; }
			
			/// Overloaded Copy Constructor, so we keep track of how many instances we have.
			Resource(const Resource& resource)
			: BaseResource(resource)
			, mResource(resource.mResource)
			{
				instance();
			}
			
			/// Overloaded Assignment Operator to ensure we keep track of everything properly.
			Resource& operator=(const Resource& resource)
			{
				if (this != &resource) { // if someone's being daft and assigning ourselves, do nothing else we're likely to commit suicide.
					remove();
					
					BaseResource::operator=(resource);
					mResource = resource.mResource;
					
					instance();
				}
				
				return *this;
			}
			
			/// Overloaded Equals Operator for pointer checking
			bool operator==(const Resource& resource)
			{
				return (mResource == resource.mResource);
			}
			
			/// Overloaded Equals Operator for 0 pointer checking
			bool operator==(const void* rhs)
			{
				return (reinterpret_cast<void*>(mResource) == rhs);
			}
			
			/// Overloaded Not Equals Operator for pointer checking
			bool operator!=(const Resource& resource)
			{
				return !(*this == resource);
			}
			
			/// Overloaded Not Equals Operator for 0 pointer checking
			bool operator!=(const void* rhs)
			{
				return !(*this == rhs);
			}
			
		protected:
			/// Protected Constructor so we can't create Resources all over the place.
			Resource(const Resources::Group group, const Resources::Type type, const Resources::Id id, T_Resource* const resource)
			: BaseResource(group, type, id)
			, mResource(resource)
			{
			}
			
			/// Delete the resource - protected and should only be called from ResourceBank through BaseResource.
			void purge() 
			{
				if (0 != mResource) {
					delete mResource; 
					mResource = 0;
				}
			}
			
			void instance()
			{
				++mCount;
			}

			void remove()
			{
				if (mCount > 0U)
					--mCount;
	
				if (mCount == 0U)
					purge();
			}
			
		private:
			T_Resource* mResource;
	};	
}

#endif
