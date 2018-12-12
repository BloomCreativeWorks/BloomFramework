#include "Audio/MusicStore.h"
#include "Exception.h"

namespace bloom::audio {
	TrackPtr MusicStore::load(const std::filesystem::path& filePath) {
		auto res = m_store.try_emplace(filePath.u8string(), std::make_shared<MusicTrack>(filePath));
		return res.first->second;
	}

	TrackPtr MusicStore::at(const std::filesystem::path& filePath) const {
		auto trackIt{ m_store.find(filePath.u8string()) };
		if (trackIt != m_store.end())
			return trackIt->second;
		else
			throw Exception("[MusicStore] Can't get track \"" + filePath.u8string() + "\".\nIs it loaded?");
	}

	TrackPtr MusicStore::find(const std::filesystem::path& filePath) const noexcept {
		auto trackIt{ m_store.find(filePath.u8string()) };
		if (trackIt != m_store.end())
			return trackIt->second;
		else
			return nullptr;
	}

	void MusicStore::unload(const std::filesystem::path& filePath) {
		auto trackIt = m_store.find(filePath.u8string());
		if (trackIt != m_store.end())
			m_store.erase(trackIt);
	}

	void MusicStore::unloadAll() noexcept {
		m_store.clear();
	}

	TrackPtr MusicStore::operator[](const std::filesystem::path& key) const noexcept {
		return find(key);
	}
}