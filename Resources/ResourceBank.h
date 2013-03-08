#ifndef _RESOURCE_BANK_H_
#define _RESOURCE_BANK_H_

#include "../GLESGAETypes.h"
#include "Resource.h"

#include <vector>
#include <cassert>

namespace GLESGAE
{
	template <typename T_Resource> class ResourceBank
	{
		public:
			ResourceBank() : mIdToData(), mFreeList(), mDataBank() {}
			~ResourceBank() { for (typename std::vector<T_Resource*>::iterator itr(mDataBank.begin()); itr < mDataBank.end(); ++itr) delete *itr; }
			
			/// Add a single Datum manually, and return the Resource Id.
			/// \return Resource Id for the datum submitted.
			Resource<T_Resource> add(T_Resource* const datum);
			
			/// Add a group of Resources, and return the Resource Ids.
			/// \return Array of resource ids in order of the data submitted.
			std::vector<Resource<T_Resource> > addGroup(const std::vector<T_Resource*>& data);
			
			/// Get a Datum.
			/// \return Datum.
			T_Resource* get(const Resource<T_Resource>& resourceId) const;
			
			/// Get a Group of Data.
			/// \return Array of Data.
			std::vector<T_Resource*> getGroup(const std::vector<Resource<T_Resource> >& resourceIds) const;
			
			/// Remove a Resource.
			void remove(const Resource<T_Resource>& resourceId);
			
			/// Remove a Group of Resources.
			void removeGroup(const std::vector<Resource<T_Resource> >& resourceIds);
			
		protected:
			/// Calculate the next resource id.
			/// \return Resource Id of the next datum.
			Resources::Id nextId();
			
			/// Find the dataId from this ResourceId
			/// \return Data Id of this Resource.
			unsigned int findDatum(const Resource<T_Resource>& id) const;
			
		private:
			std::vector<unsigned int> mIdToData; //!< For converting Resource Ids to Data indices.
			std::vector<unsigned int> mFreeList;
			std::vector<T_Resource*> mDataBank;
	};
	
	template <typename T_Resource> Resource<T_Resource> ResourceBank<T_Resource>::add(T_Resource* const datum)
	{
		mDataBank.push_back(datum);
		return Resource<T_Resource>(nextId());
	}

	template <typename T_Resource> std::vector<Resource<T_Resource> > ResourceBank<T_Resource>::addGroup(const std::vector<T_Resource*>& data)
	{
		std::vector<Resource<T_Resource> > ids;
		for (typename std::vector<T_Resource*>::const_iterator itr(data.begin()); itr < data.end(); ++itr)
			ids.push_back(add(*itr));
			
		return ids;
	}

	template <typename T_Resource> T_Resource* ResourceBank<T_Resource>::get(const Resource<T_Resource>& resourceId) const
	{
		const unsigned int id(findDatum(resourceId));
		assert(GLESGAE::INVALID != id);
		
		return mDataBank[id];
	}
	
	template <typename T_Resource> std::vector<T_Resource*> ResourceBank<T_Resource>::getGroup(const std::vector<Resource<T_Resource> >& group) const
	{
		std::vector<T_Resource*> data;
		for (typename std::vector<Resource<T_Resource> >::const_iterator itr(group.begin()); itr < group.end(); ++itr)
			data.push_back(get(*itr));
			
		return data;
	}
	
	template <typename T_Resource> void ResourceBank<T_Resource>::remove(const Resource<T_Resource>& resourceId)
	{
		const unsigned int id(findDatum(resourceId));
		assert(GLESGAE::INVALID != id);
		
		delete mDataBank[id];
		mDataBank[id] = *(mDataBank.end() - 1U);
		delete mDataBank[mDataBank.size() - 1U];
		mIdToData[mDataBank.size() - 1U] = resourceId.getId();
		mDataBank.pop_back();
	}

	template <typename T_Resource> void ResourceBank<T_Resource>::removeGroup(const std::vector<Resource<T_Resource> >& group)
	{
		for (typename std::vector<Resource<T_Resource> >::const_iterator itr(group.begin()); itr < group.end(); ++itr)
			remove(*itr);
	}
	
	template <typename T_Resource> Resources::Id ResourceBank<T_Resource>::nextId()
	{
		Resources::Id id(GLESGAE::INVALID);
		// Check free slots first.
		if (false == mFreeList.empty()) {
			id = *(mFreeList.end() - 1U);
			mFreeList.pop_back();
			mIdToData[id] = mDataBank.size() - 1U;
		}
		
		// No free slots, so a new slot please.
		if (GLESGAE::INVALID == id) {
			id = mIdToData.size();
			mIdToData.push_back(mDataBank.size() - 1U);
		}
		
		return id;
	}
	
	template <typename T_Resource> unsigned int ResourceBank<T_Resource>::findDatum(const Resource<T_Resource>& id) const
	{
		assert(id.getId() < mIdToData.size());
		return (mIdToData[id.getId()]);
	}
}

#endif
