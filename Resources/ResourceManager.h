#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include "ResourceBank.h"

#include <string>
#include <map>
#include <cassert>

namespace GLESGAE
{
	class ResourceManager
	{
		friend class BaseResource;
		public:
			ResourceManager() : mResourceBanks() {}
			~ResourceManager() { assert(mResourceBanks.empty()); }
			
			/// Create a new Resource Bank of the specified
			template <typename T_Resource> ResourceBank<T_Resource>& createBank(const Resources::Type bankType);
			
			/// Retrieve a Resource Bank
			template <typename T_Resource> ResourceBank<T_Resource>& getBank(const Resources::Id bankId, const Resources::Type bankType);
			
			/// Delete a Resource Bank
			template <typename T_Resource> void removeBank(const Resources::Id bankId, const Resources::Type bankType);
			
			/// Load Resource Bank from Disk
			template <typename T_Resource> void loadBankResources(const std::string& bankSet, const Resources::Id bankId, const Resources::Type bankType);
			
			/// Save Resource Bank to Disk
			template <typename T_Resource> void saveBankResources(const std::string& bankSet, const Resources::Id bankId, const Resources::Type bankType);
			
		private:
			// A map denoting the name of a resource bank, and the resource bank pointer itself.
			std::map<Resources::Id, BaseResourceBank*> mResourceBanks;
	};
	
	template <typename T_Resource> ResourceBank<T_Resource>& ResourceManager::createBank(const Resources::Type bankType)
	{
		// TODO: check bank doesn't already exist.
		Resources::Id bankId = mResourceBanks.size();
		mResourceBanks[bankId] = new ResourceBank<T_Resource>(bankId, bankType);
		return *(reinterpret_cast<ResourceBank<T_Resource>*>(mResourceBanks[bankId]));
	}
	
	template <typename T_Resource> ResourceBank<T_Resource>& ResourceManager::getBank(const Resources::Id bankId, const Resources::Type)
	{
		// TODO: check bank actually exists.
		assert(bankId != INVALID);
		return *(reinterpret_cast<ResourceBank<T_Resource>*>(mResourceBanks[bankId]));
	}
	
	template <typename T_Resource> void ResourceManager::removeBank(const Resources::Id bankId, const Resources::Type /*typeId*/)
	{
		std::map<Resources::Id, BaseResourceBank*>::iterator bank(mResourceBanks.find(bankId));
		if (bank != mResourceBanks.end()) {
			// TODO: Check that the bankType matches up!
			delete reinterpret_cast<ResourceBank<T_Resource>*>(bank->second);
			bank->second = 0;
		}
	
		// TODO: Error that we can't find this bank!
	}
/*	
	template <typename T_Resource> void ResourceManager::loadBankResources(const std::string& bankSet, const Resources::Id bankId, const Resources::Type bankType)
	{
	}
	
	template <typename T_Resource> void ResourceManager::saveBankResources(const std::string& bankSet, const Resources::Id bankId, const Resources::Type bankType)
	{
	}
*/
}

#endif
