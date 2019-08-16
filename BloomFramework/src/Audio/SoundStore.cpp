#include "Audio/SoundStore.h"
#include "Exception.h"

namespace bloom::audio {
	SoundChunkPtr SoundStore::load(const std::filesystem::path & filePath) {
		if (!std::filesystem::exists(filePath))
			throw Exception{ "SoundStore::load", "File \"" + filePath.u8string() + "\" not exists" };

		if (filePath.extension() != std::filesystem::path(L".wav"))
			throw Exception{ "SoundStore::load", "non-wav file provided, use wav files only" };

		auto chunkIt = m_store.find(filePath.u8string());
		if (chunkIt != m_store.end())
			return chunkIt->second;

		SoundChunkPtr ptr = std::make_shared<SoundChunk>(filePath.u8string(), true);
		m_store.emplace(filePath.u8string(), ptr);

		return ptr;
	}

	SoundChunkPtr SoundStore::find(const std::filesystem::path & filePath) {
		auto chunkIt = m_store.find(filePath.u8string());
		if (chunkIt != m_store.end())
			return chunkIt->second;
		throw Exception{ "SoundStore::find", "File \"" + filePath.u8string() + "\" not loaded" };
	}

	SoundChunkPtr SoundStore::find(std::nothrow_t, const std::filesystem::path & filePath) noexcept {
		auto chunkIt = m_store.find(filePath.u8string());
		if (chunkIt != m_store.end())
			return chunkIt->second;
		else {
			return nullptr;
		}
	}

	void SoundStore::unload(const std::filesystem::path & filePath) {
		auto chunkIt = m_store.find(filePath.u8string());
		if (chunkIt != m_store.end()) {
			m_store.erase(chunkIt);
		}
	}

	void SoundStore::unloadAll() {
		m_store.clear();
	}
}