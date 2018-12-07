#include "Audio/MusicStore.h"
#include "Exception.h"

namespace bloom::audio {
	TrackPtr MusicStore::load(const std::filesystem::path & filePath) {
		if (!std::filesystem::exists(filePath))
			throw Exception("[MusicStore::load] " + filePath.u8string() + " not exists");

		auto trackIt = m_store.find(filePath.u8string());
		if (trackIt != m_store.end())
			return trackIt->second;

		TrackPtr ptr = std::make_shared<MusicTrack>(filePath.u8string());
		m_store.emplace(filePath.u8string(), ptr);
		return ptr;
	}

	TrackPtr MusicStore::at(const std::filesystem::path & filePath) const {
		auto trackIt{ m_store.find(filePath.u8string()) };
		if (trackIt != m_store.end())
			return trackIt->second;
		else
			throw Exception("[Music Store] Can't get track \"" + filePath.u8string() + "\".\nIs it loaded?");
	}

	TrackPtr MusicStore::find(const std::filesystem::path & filePath) const {
		auto trackIt{ m_store.find(filePath.u8string()) };
		if (trackIt != m_store.end())
			return trackIt->second;
		else
			return nullptr;
	}

	void MusicStore::unload(const std::filesystem::path & filePath) {
		auto trackIt = m_store.find(filePath.u8string());
		if (trackIt != m_store.end())
			m_store.erase(trackIt);
	}

	void MusicStore::unloadAll() noexcept {
		m_store.clear();
	}

	TrackPtr MusicStore::operator[](const std::filesystem::path & key) const noexcept {
		return find(key);
	}
}