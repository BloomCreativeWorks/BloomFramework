#include "Audio/SoundStore.h"
#include "Exception.h"

namespace bloom::audio {
	SoundStore::~SoundStore() {
		unloadAll();
	}

	SoundChunkPtr SoundStore::load(const std::string & filePath) {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;

		SoundChunkPtr ptr = std::make_shared<SoundChunk>(filePath);
		m_store.emplace(filePath, ptr);

		return ptr;
	}

	SoundChunkPtr SoundStore::find(const std::string & filePath) {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;
		else {
			throw Exception("[Sound Store] Can't get SoundFX \"" + filePath + "\".\nIs it loaded?");
		}
	}

	SoundChunkPtr SoundStore::find(std::nothrow_t, const std::string & filePath) noexcept {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;
		else {
			return nullptr;
		}
	}

	void SoundStore::unload(const std::string & filePath) {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end()) {
			m_store.erase(SoundFXIt);
		}
	}

	void SoundStore::unloadAll() {
		m_store.clear();
	}
}