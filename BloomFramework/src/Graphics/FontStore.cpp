#include "Graphics/FontStore.h"

namespace bloom::graphics {
	FontPtr FontStore::load(const std::filesystem::path & filePath, size_t presetNumber, FontStyle style) {
		if (auto fontIt = m_store.find(presetNumber); fontIt != m_store.end()) {
			std::clog << "[FontStore::load] font preset with that name already exists, returning that instead" << std::endl;
			return fontIt->second;
		}

		FontPtr ptr = std::make_shared<Font>(filePath, style);
		m_store.emplace(presetNumber, ptr);
		return ptr;
	}

	FontPtr FontStore::find(size_t presetNumber) const noexcept {
		if (auto fontIt = m_store.find(presetNumber); fontIt != m_store.end())
			return fontIt->second;
		else
			return nullptr;
	}

	void FontStore::unload(size_t presetNumber) {
		if (auto fontIt = m_store.find(presetNumber); fontIt != m_store.end())
			m_store.erase(fontIt);
	}

	FontPtr FontStore::operator[](size_t key) const noexcept {
		return find(key);
	}
}