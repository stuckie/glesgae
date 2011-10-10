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
		// It's a friend to itself to deal with the recast functionality.
		template <typename T_ResourceCast> friend class Resource;
		public:
			/// Dummy Constructor for creation of empty Resources.
			Resource() : BaseResource(Resources::INVALID, Resources::INVALID, Resources::INVALID), mResource(0) {}
			~Resource() { remove(); }
			
			/// Constructor for taking ownership over raw pointers.
			Resource(T_Resource* const resource) : BaseResource(Resources::INVALID, Resources::INVALID, Resources::INVALID), mResource(resource) { instance(); }
			
			/// Pointer Operator overload to return the actual resource.
			T_Resource* operator-> () { return mResource; }
			
			/// Const Pointer Operator overload.
			T_Resource* operator-> () const { return mResource; }
			
			/// Dereference Operator overload to return the actual resource.
			T_Resource& operator* () { return *mResource; }
			
			/// Const Dereference operator overload.
			const T_Resource& operator* () const { return *mResource; }
			
			/// Recast Copy into a another Resource.
			template <typename T_ResourceCast> Resource<T_ResourceCast> recast()
			{
				Resource<T_ResourceCast> newResource;
				newResource.mGroup = mGroup;
				newResource.mType = mType;
				newResource.mId = mId;
				newResource.mCount = mCount;
				newResource.mResource = reinterpret_cast<T_ResourceCast*>(mResource);
				instance();
				return newResource;
			}
			
			/// Recast Copy into a another Resource.
			template <typename T_ResourceCast> const Resource<T_ResourceCast> recast() const
			{
				Resource<T_ResourceCast> newResource;
				newResource.mGroup = mGroup;
				newResource.mType = mType;
				newResource.mId = mId;
				newResource.mCount = mCount;
				newResource.mResource = reinterpret_cast<T_ResourceCast*>(mResource);
				instance();
				return newResource;
			}
			
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
					BaseResource::operator=(resource);
					mResource = resource.mResource;
					
					instance();
				}
				
				return *this;
			}
			
			/// Overloaded Equals Operator for pointer checking.
			bool operator==(const Resource& resource)
			{
				return (mResource == resource.mResource);
			}
			
			/// Overloaded Equals Operator for 0 pointer checking.
			bool operator==(const void* rhs)
			{
				return (reinterpret_cast<void*>(mResource) == rhs);
			}
			
			/// Overloaded Not Equals Operator for pointer checking.
			bool operator!=(const Resource& resource)
			{
				return !(*this == resource);
			}
			
			/// Overloaded Not Equals Operator for 0 pointer checking.
			bool operator!=(const void* rhs)
			{
				return !(*this == rhs);
			}
			
		protected:
			/// Protected Constructor so we can't create Managed Resources all over the place.
			Resource(const Resources::Group group, const Resources::Type type, const Resources::Id id, T_Resource* const resource)
			: BaseResource(group, type, id)
			, mResource(resource)
			{
			}
			
			/// Delete the actual resource.
			void purge() 
			{
				if (0 != mResource) {
					delete mResource; 
					mResource = 0;
				}
			}
			
			/// Increase the instance count of this Resource.
			void instance() const
			{
				++(*mCount);
			}

			/// Remove an instance count of this Resource, and if there are no more instances, purge it.
			void remove()
			{
				if ((*mCount) > 0U)
					--(*mCount);
	
				if ((*mCount) == 0U)
					purge();
			}
			
		private:
			T_Resource* mResource;
	};	
}

#endif
