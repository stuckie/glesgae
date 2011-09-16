#ifndef _RESOURCE_BANK_H_
#define _RESOURCE_BANK_H_

#include "Resource.h"
#include "BaseResourceBank.h"

#include <vector>
#include <cassert>

namespace GLESGAE
{
	template <typename T_Resource> class ResourceBank : public BaseResourceBank
	{
		// Resource is a friend to access instance.
		friend class Resource<T_Resource>;
		public:
			ResourceBank(const Resources::Id id, const Resources::Type type) : BaseResourceBank(id, type), mResources() {}
			~ResourceBank();
			
			/// Create a new resource group.
			Resources::Group newGroup();
			
			/// Get an entire Resource group.
			const std::vector<Resource<T_Resource>*>& getGroup(const Resources::Group groupId) const;
			
			/// Remove Group
			void removeGroup(const Resources::Group groupId);
			
			/// Add a single Resource manually, and return the Resource version.
			Resource<T_Resource>& add(const Resources::Group groupId, const Resources::Type typeId, T_Resource* const resource);
			
			/// Add a group of Resources, and return the Group Id
			Resources::Group addGroup(const std::vector<Resource<T_Resource>*>& resourceGroup);
			
			/// Get a Resource immediately
			Resource<T_Resource>& get(const Resources::Group groupId, const Resources::Id resourceId);	
			
		private:
			// Scary stuff... an array ( which we can access via ID - Group Id for example ) holding another array.
			// Second array holds a pair, this time of the Resource Count and the actual Resource itself - so we can wipe out the resource when the count reaches 0.
			std::vector<std::vector<Resource<T_Resource>*> > mResources;
	};
	
	template <typename T_Resource> ResourceBank<T_Resource>::~ResourceBank()
	{
		for (unsigned int index(0U); index < mResources.size(); ++index)
			removeGroup(index);
	}
		
	template <typename T_Resource> Resources::Group ResourceBank<T_Resource>::newGroup()
	{
		std::vector<Resource<T_Resource>*> resourceArray;
		mResources.push_back(resourceArray);
	
		return mResources.size() - 1U;
	}
	
	template <typename T_Resource> const std::vector<Resource<T_Resource>*>& ResourceBank<T_Resource>::getGroup(const Resources::Group groupId) const
	{
		// TODO: Scream if that groupId isn't valid, or doesn't exist...
		if (Resources::INVALID == groupId) {
			assert(0);
			return;
		}
			
		return mResources[groupId];
	}

	template <typename T_Resource> void ResourceBank<T_Resource>::removeGroup(const Resources::Group groupId)
	{
		// TODO: Scream if that groupId isn't valid or doesn't exist...
		if (Resources::INVALID == groupId)
			return;
	
		std::vector<Resource<T_Resource>*>& resourceArray(mResources[groupId]);
		for (typename std::vector<Resource<T_Resource>*>::iterator itr(resourceArray.begin()); itr < resourceArray.end(); ++itr) 			{
			if (0 != (*itr)) {
				if ((*itr)->getCount() > 1U) {
					// TODO: scream bloody mary that there's still something using this resource.
					continue;
				}
				else {
					delete (*itr);
					(*itr) = 0;
				}
			}
		}
	
		resourceArray.clear();
	}
	
	template <typename T_Resource> Resource<T_Resource>& ResourceBank<T_Resource>::add(const Resources::Group groupId, const Resources::Type typeId, T_Resource* const resource)
	{
		std::vector<Resource<T_Resource>*>& resourceArray(mResources[groupId]);
		const Resources::Id resourceId(resourceArray.size());
	
		resourceArray.push_back(new Resource<T_Resource>(groupId, typeId, resourceId, resource));
		
		resourceArray[resourceId]->setCount(1U);
		return (*(resourceArray[resourceId]));
	}
	
	template <typename T_Resource> Resources::Group ResourceBank<T_Resource>::addGroup(const std::vector<Resource<T_Resource>*>& resourceGroup)
	{
		const Resources::Group groupId(mResources.size());
		
		mResources.push_back(resourceGroup);
		return groupId;
	}

	template <typename T_Resource> Resource<T_Resource>& ResourceBank<T_Resource>::get(const Resources::Group groupId, const Resources::Id resourceId)
	{
		assert(groupId != Resources::INVALID);
		assert(resourceId != Resources::INVALID);
		Resource<T_Resource>* resource(mResources[groupId][resourceId]);
		return *(resource);
	}

}


#endif
