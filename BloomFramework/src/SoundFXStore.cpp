#include "SoundFXStore.h"
#include "Exception.h"

namespace bloom {
	SoundFXPtr SoundFXStore::load(const std::string & filePath) {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;

		SoundFXPtr ptr = std::make_shared<SoundFX>(filePath);
		m_store.emplace(filePath, ptr);
		m_channels += m_def_channels4sound;
		Mix_AllocateChannels(m_channels + m_extraChannels);

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
			m_channels -= m_def_channels4sound;
			Mix_AllocateChannels(m_channels + m_extraChannels);
		}
	}

	void SoundFXStore::_extraChannels(int extraChannels) {
		if (extraChannels < 0) extraChannels *= -1;
		m_extraChannels = extraChannels;
		Mix_AllocateChannels(m_channels + m_extraChannels);
	}
}