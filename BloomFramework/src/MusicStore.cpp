#include "MusicStore.h"
#include "Exception.h"

namespace bloom::audio {
	MusicStore::MusicStore() {
		if (obj_qnt > 0)
			throw Exception("Creating more than 1 object of a `MusicFull` class is forbidden!");
		obj_qnt++;
	}

	MusicStore::~MusicStore() {
		unloadAll();
	}

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

	TrackPtr MusicStore::find(std::nothrow_t, const std::string & filePath) noexcept {
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

	void MusicStore::unloadAll() {
		m_store.clear();
	}
}