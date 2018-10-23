#include "Audio/SoundStore.h"
#include "Exception.h"

namespace bloom::audio {
	SoundStore::~SoundStore() {
		unloadAll();
	}

	SoundChunkPtr SoundStore::load(const std::filesystem::path & filePath) {
		if (!std::filesystem::exists(filePath)) {
			throw Exception("[SoundStore::load] " + filePath.u8string() + " not exists");
		}

		auto SoundFXIt = m_store.find(filePath.u8string());
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;

		SoundChunkPtr ptr = std::make_shared<SoundChunk>(filePath.u8string());
		m_store.emplace(filePath.u8string(), ptr);

		return ptr;
	}

	SoundChunkPtr SoundStore::find(const std::filesystem::path & filePath) {
		auto SoundFXIt = m_store.find(filePath.u8string());
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;
		else {
			throw Exception("[Sound Store] Can't get SoundFX \"" + filePath.u8string() + "\".\nIs it loaded?");
		}
	}

	SoundChunkPtr SoundStore::find(std::nothrow_t, const std::filesystem::path & filePath) noexcept {
		auto SoundFXIt = m_store.find(filePath.u8string());
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;
		else {
			return nullptr;
		}
	}

	void SoundStore::unload(const std::filesystem::path & filePath) {
		auto SoundFXIt = m_store.find(filePath.u8string());
		if (SoundFXIt != m_store.end()) {
			m_store.erase(SoundFXIt);
		}
	}

	void SoundStore::unloadAll() {
		m_store.clear();
	}
}