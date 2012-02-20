#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include "ResourceBank.h"
#include <string>

namespace GLESGAE
{
	class ResourceManager
	{
		friend class BaseResource;
		public:
			ResourceManager() : mResourceBanks() {}
			
			/// Create a new Resource Bank of the specified
			template <typename T_Resource> ResourceBank<T_Resource>& createBank(const Resources::Type bankType);
			
			/// Retrieve a Resource Bank
			template <typename T_Resource> ResourceBank<T_Resource>& getBank(const Resources::Id bankId, const Resources::Type bankType);
			
			/// Delete a Resource Bank
			template <typename T_Resource> void removeBank(const Resources::Id bankId, const Resources::Type bankType);
			
			/// Load Resource Bank from Disk
			template <typename T_Resource> Resources::Id loadBankResources(const std::string& bankSet, const Resources::Type bankType);
			
			/// Save Resource Bank to Disk
			template <typename T_Resource> void saveBankResources(const std::string& bankSet, const Resources::Id bankId, const Resources::Type bankType);
			
		private:
			// An array denoting the id of a resource bank, and the resource bank itself.
			std::vector<Resource<BaseResourceBank> > mResourceBanks;
	};
	
	template <typename T_Resource> ResourceBank<T_Resource>& ResourceManager::createBank(const Resources::Type bankType)
	{
		// TODO: check bank doesn't already exist.
		// TODO: find a blank space.
		Resources::Id bankId = mResourceBanks.size();
		mResourceBanks.push_back(Resource<BaseResourceBank>(new ResourceBank<T_Resource>(bankId, bankType)));
		return *((mResourceBanks[bankId]).recast<ResourceBank<T_Resource> >());
	}
	
	template <typename T_Resource> ResourceBank<T_Resource>& ResourceManager::getBank(const Resources::Id bankId, const Resources::Type)
	{
		// TODO: check bank actually exists.
		assert(bankId != INVALID);
		return *((mResourceBanks[bankId]).recast<ResourceBank<T_Resource> >());
	}
	
	template <typename T_Resource> void ResourceManager::removeBank(const Resources::Id bankId, const Resources::Type typeId)
	{
		if (bankId < mResourceBanks.size()) {
			assert(mResourceBanks[bankId]->getType() == typeId);
			mResourceBanks[bankId] = Resource<BaseResourceBank>();
		} else {	// out of bounds...
			assert(0);
		}
	}
/*	
	template <typename T_Resource> Resources::Id ResourceManager::loadBankResources(const std::string& bankSet, const Resources::Type bankType)
	{
	}
	
	template <typename T_Resource> void ResourceManager::saveBankResources(const std::string& bankSet, const Resources::Id bankId, const Resources::Type bankType)
	{
	}
*/
}

#endif
