#include "Graphics/FontStore.h"

namespace bloom::graphics {
	FontPtr FontStore::load(const std::filesystem::path & filePath, const std::string & presetName, FontStyle style) {
		if (auto fontIt = m_store.find(presetName); fontIt != m_store.end()) {
			std::clog << "[FontStore::laod]Font preset with that name already exists, returning that instead." << std::endl;
			return fontIt->second;
		}

		FontPtr ptr = std::make_shared<Font>(filePath, style);
		m_store.emplace(presetName, ptr);
		return ptr;
	}

	FontPtr FontStore::find(const std::string & presetName) const noexcept {
		if (auto fontIt = m_store.find(presetName); fontIt != m_store.end())
			return fontIt->second;
		else
			return nullptr;
	}

	void FontStore::unload(const std::string & presetName) {
		if (auto fontIt = m_store.find(presetName); fontIt != m_store.end())
			m_store.erase(fontIt);
	}

	FontPtr FontStore::operator[](const std::string & key) const noexcept
	{
		return find(key);
	}
}