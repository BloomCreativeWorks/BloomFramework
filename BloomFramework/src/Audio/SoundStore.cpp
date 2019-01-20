//#include "Audio/SoundStore.h"
//#include "Exception.h"
//
//namespace bloom::audio {
//	SoundStore& SoundStore::store() {
//		static SoundStore store_instance;
//		return store_instance;
//	}
//
//	ChunkPtr SoundStore::load(const std::filesystem::path& filePath) {
//		return m_store.try_emplace(filePath, std::make_shared<SoundChunk>(filePath)).first->second;
//	}
//
//	ChunkPtr SoundStore::at(const std::filesystem::path& filePath) const {
//		auto SoundChunkIt{ m_store.find(filePath) };
//		if (SoundChunkIt != m_store.end())
//			return SoundChunkIt->second;
//		else
//			throw Exception("[SoundStore] Can't get chunk \"" + filePath.u8string() + "\".\nIs it loaded?");
//	}
//
//	ChunkPtr SoundStore::find(const std::filesystem::path& filePath) const noexcept {
//		auto SoundChunkIt{ m_store.find(filePath) };
//		if (SoundChunkIt != m_store.end())
//			return SoundChunkIt->second;
//		else
//			return nullptr;
//	}
//
//	void SoundStore::unload(const std::filesystem::path& filePath) {
//		m_store.erase(filePath);
//	}
//
//	void SoundStore::unloadAll() noexcept {
//		m_store.clear();
//	}
//
//	ChunkPtr SoundStore::operator[](const std::filesystem::path& key) const noexcept {
//		return find(key);
//	}
//}