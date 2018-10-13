#include "SoundFXStore.h"
#include "Exception.h"

namespace bloom {
	SoundChunkPtr SoundFXStore::load(const std::string & filePath) {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;

		SoundChunkPtr ptr = std::make_shared<SoundChunk>(filePath);
		m_store.emplace(filePath, ptr);

		return ptr;
	}

	SoundChunkPtr SoundFXStore::find(const std::string & filePath) {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;
		else {
			throw Exception("[Music Store] Can't get SoundFX \"" + filePath + "\".\nIs it loaded?");
		}
	}

	SoundChunkPtr SoundFXStore::find(std::nothrow_t, const std::string & filePath) noexcept {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;
		else {
			return nullptr;
		}
	}

	void SoundFXStore::unload(const std::string & filePath) {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end()) {
			m_store.erase(SoundFXIt);
		}
	}

	void SoundFXStore::unload_all() {
		m_store.clear();
	}
}