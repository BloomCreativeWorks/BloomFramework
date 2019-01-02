#include "Audio/MusicStore.h"
#include "Exception.h"

namespace bloom::audio {
	MusicStore& MusicStore::store() {
		static MusicStore store_instance;
		return store_instance;
	}

	TrackPtr MusicStore::load(const std::filesystem::path& filePath) {
		return m_store.try_emplace(filePath, std::make_shared<MusicTrack>(filePath)).first->second;
	}

	TrackPtr MusicStore::at(const std::filesystem::path& filePath) const {
		auto trackIt{ m_store.find(filePath) };
		if (trackIt != m_store.end())
			return trackIt->second;
		else
			throw Exception("[MusicStore] Can't get track \"" + filePath.u8string() + "\".\nIs it loaded?");
	}

	TrackPtr MusicStore::find(const std::filesystem::path& filePath) const noexcept {
		auto trackIt{ m_store.find(filePath) };
		if (trackIt != m_store.end())
			return trackIt->second;
		else
			return nullptr;
	}

	void MusicStore::unload(const std::filesystem::path& filePath) {
		m_store.erase(filePath);
	}

	void MusicStore::unloadAll() noexcept {
		m_store.clear();
	}

	TrackPtr MusicStore::operator[](const std::filesystem::path& key) const noexcept {
		return find(key);
	}
}