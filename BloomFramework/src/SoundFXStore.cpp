// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SoundFXStore.h"
#include "Exception.h"

namespace bloom {
	SoundFXPtr SoundFXStore::load(const std::string & filePath) {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;

		SoundFXPtr ptr = std::make_shared<SoundFX>(filePath);
		m_store.emplace(filePath, ptr);
		Mix_AllocateChannels(static_cast<int>(m_store.size()));

		return ptr;
	}

	SoundFXPtr SoundFXStore::find(const std::string & filePath) {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;
		else {
			throw Exception("[Music Store] Can't get SoundFX \"" + filePath + "\".\nIs it loaded?");
		}
	}

	SoundFXPtr SoundFXStore::find(std::nothrow_t, const std::string & filePath) noexcept {
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
			Mix_AllocateChannels(static_cast<int>(m_store.size()));
		}
	}
}