#include "SoundFXStore.h"
#include "Exception.h"

namespace bloom {
	SoundFXPtr SoundFXStore::load(const std::string & filePath) {
		auto SoundFXIt = m_store.find(filePath);
		if (SoundFXIt != m_store.end())
			return SoundFXIt->second;

		SoundFXPtr ptr = std::make_shared<SoundFX>(filePath, !m_autochannels);
		m_store.emplace(filePath, ptr);

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
		}
	}

	void SoundFXStore::disableAutoChannels(bool state) {
		m_autochannels = !state;
		if (!m_autochannels)
			Mix_AllocateChannels(m_extraChannels);
	}

	void SoundFXStore::manageExtraChannels(int qnt) {
		m_extraChannels = (qnt == 0 ? 1 : (qnt < 0 ? -qnt : qnt));
		if (!m_autochannels)
			Mix_AllocateChannels(m_extraChannels);
	}
}