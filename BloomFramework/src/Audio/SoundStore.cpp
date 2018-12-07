#include "Audio/SoundStore.h"
#include "Exception.h"

namespace bloom::audio {
	ChunkPtr SoundStore::load(const std::filesystem::path & filePath) {
		if (!std::filesystem::exists(filePath))
			throw Exception("[SoundStore::load] " + filePath.u8string() + " not exists");

		if (filePath.extension() != std::filesystem::path(L".wav"))
			throw Exception("[SoundStore::load] non-wav file provided, use wav files only");

		auto SoundChunkIt = m_store.find(filePath.u8string());
		if (SoundChunkIt != m_store.end())
			return SoundChunkIt->second;

		ChunkPtr ptr = std::make_shared<SoundChunk>(filePath.u8string(), true);
		m_store.emplace(filePath.u8string(), ptr);

		return ptr;
	}

	ChunkPtr SoundStore::at(const std::filesystem::path & filePath) const {
		auto SoundChunkIt{ m_store.find(filePath.u8string()) };
		if (SoundChunkIt != m_store.end())
			return SoundChunkIt->second;
		else
			throw Exception("[Sound Store] Can't get SoundFX \"" + filePath.u8string() + "\".\nIs it loaded?");
	}

	ChunkPtr SoundStore::find(const std::filesystem::path & filePath) const noexcept {
		auto SoundChunkIt{ m_store.find(filePath.u8string()) };
		if (SoundChunkIt != m_store.end())
			return SoundChunkIt->second;
		else
			return nullptr;
	}

	void SoundStore::unload(const std::filesystem::path & filePath) {
		auto SoundChunkIt = m_store.find(filePath.u8string());
		if (SoundChunkIt != m_store.end())
			m_store.erase(SoundChunkIt);
	}

	void SoundStore::unloadAll() noexcept {
		m_store.clear();
	}

	ChunkPtr SoundStore::operator[](const std::filesystem::path & key) const noexcept {
		return find(key);
	}
}