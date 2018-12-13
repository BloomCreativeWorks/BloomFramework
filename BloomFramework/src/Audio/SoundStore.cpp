#include "Audio/SoundStore.h"
#include "Exception.h"

namespace bloom::audio {
	ChunkPtr SoundStore::load(const std::filesystem::path& filePath) {
		auto res = m_store.try_emplace(filePath, std::make_shared<SoundChunk>(filePath));
		return res.first->second;
	}

	ChunkPtr SoundStore::at(const std::filesystem::path& filePath) const {
		auto SoundChunkIt{ m_store.find(filePath) };
		if (SoundChunkIt != m_store.end())
			return SoundChunkIt->second;
		else
			throw Exception("[SoundStore] Can't get chunk \"" + filePath.u8string() + "\".\nIs it loaded?");
	}

	ChunkPtr SoundStore::find(const std::filesystem::path& filePath) const noexcept {
		auto SoundChunkIt{ m_store.find(filePath) };
		if (SoundChunkIt != m_store.end())
			return SoundChunkIt->second;
		else
			return nullptr;
	}

	void SoundStore::unload(const std::filesystem::path& filePath) {
		m_store.erase(filePath);
	}

	void SoundStore::unloadAll() noexcept {
		m_store.clear();
	}

	ChunkPtr SoundStore::operator[](const std::filesystem::path& key) const noexcept {
		return find(key);
	}
}