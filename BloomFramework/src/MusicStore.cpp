#include "MusicStore.h"
#include "Exception.h"

namespace bloom {
	TrackPtr MusicStore::load(const std::string & filePath) {
		auto trackIt = m_store.find(filePath);
		if (trackIt != m_store.end())
			return trackIt->second;

		TrackPtr ptr = std::make_shared<Music>(filePath);
		m_store.emplace(filePath, ptr);
		return ptr;
	}

	TrackPtr MusicStore::find(const std::string & filePath) {
		auto trackIt = m_store.find(filePath);
		if (trackIt != m_store.end())
			return trackIt->second;
		else {
			throw Exception("[Music Store] Can't get track \"" + filePath + "\".\nIs it loaded?");
		}
	}

	TrackPtr MusicStore::find(std::nothrow_t, const std::string & filePath) {
		auto trackIt = m_store.find(filePath);
		if (trackIt != m_store.end())
			return trackIt->second;
		else {
			return nullptr;
		}
	}

	void MusicStore::unload(const std::string & filePath) {
		auto trackIt = m_store.find(filePath);
		if (trackIt != m_store.end())
			m_store.erase(trackIt);
	}
}