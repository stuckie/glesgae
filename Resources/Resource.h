#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "BaseResource.h"
#include <cassert>

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
			Resource() : BaseResource(INVALID, INVALID_HASHSTRING, INVALID), mResource(0) {}
			~Resource()
			{ 
				if (0 != mResource) 
					remove(); 
				else {
					if (0 != mCount) {
						if ((*mCount) == 0) 
							delete mCount;
						else {
							--(*mCount);
						}
					}
				}
			}
			
			/// Constructor for taking ownership over raw pointers.
			explicit Resource(T_Resource* const resource) : BaseResource(INVALID, INVALID_HASHSTRING, INVALID), mResource(resource) { if (0 != mResource) instance(); }
			
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
				Resource<T_ResourceCast> newResource(mGroup, mType, mId, reinterpret_cast<T_ResourceCast*>(mResource));
				delete newResource.mCount;
				newResource.mCount = mCount;
				instance();
				return newResource;
			}
			
			/// Recast Copy into a another Resource.
			template <typename T_ResourceCast> const Resource<T_ResourceCast> recast() const
			{
				Resource<T_ResourceCast> newResource(mGroup, mType, mId, reinterpret_cast<T_ResourceCast*>(mResource));
				delete newResource.mCount;
				newResource.mCount = mCount;
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
					remove();
					
					BaseResource::operator=(resource);
					mResource = resource.mResource;
					
					instance();
				}
				
				return *this;
			}
			
			/// Overloaded Equals Operator for pointer checking.
			bool operator==(const Resource& resource) const
			{
				return (mResource == resource.mResource);
			}
			
			/// Overloaded Equals Operator for 0 pointer checking.
			bool operator==(const void* rhs) const
			{
				return (reinterpret_cast<void*>(mResource) == rhs);
			}
			
			/// Overloaded Not Equals Operator for pointer checking.
			bool operator!=(const Resource& resource) const
			{
				return !(*this == resource);
			}
			
			/// Overloaded Not Equals Operator for 0 pointer checking.
			bool operator!=(const void* rhs) const
			{
				return !(*this == rhs);
			}
			
			/// Increase the instance count of this Resource.
			/// Be exceptionally careful with using this manually, you will need to call remove manually as well!
			/// This is however, useful for anything that has to be sent a raw pointer which may leave C-scope.
			/// For example, Physics Engines and Scripting Languages.
			void instance() const
			{
				assert(mCount);
				++(*mCount);
			}

			/// Remove an instance count of this Resource, and if there are no more instances, purge it.
			/// Calling this manually should be used with caution, and only on a Resource which has been manually instanced.
			/// Otherwise, you will get into a situation whereby you've deleted something which still has a reference.
			/// Again, this is primarily useful for Physics Engines and Scripting Languages only.
			void remove()
			{
				assert(mCount);
				if ((*mCount) > 0U)
					--(*mCount);

				if ((*mCount) == 0U)
					purge();
			}
			
		protected:
			/// Protected Constructor so we can't create Managed Resources all over the place.
			explicit Resource(const Resources::Group group, const Resources::Type type, const Resources::Id id, T_Resource* const resource)
			: BaseResource(group, type, id)
			, mResource(resource)
			{
				instance();
			}
			
			/// Delete the actual resource.
			void purge() 
			{
				if (0 != mResource) {
					delete mResource; 
					mResource = 0;
				}
				
				if (0 != mCount) {
					delete mCount;
					mCount = 0;
				}
			}
			
		private:
			T_Resource* mResource;
	};	
}

#endif
