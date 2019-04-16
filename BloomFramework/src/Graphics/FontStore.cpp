#include "Graphics/FontStore.h"

namespace bloom::graphics {
	FontPtr FontStore::load(const std::filesystem::path& filePath, size_t presetNumber, FontStyle style) {
		if (auto fontPtr = find(presetNumber); fontPtr)
			return fontPtr;

		FontPtr ptr = std::make_shared<Font>(filePath, style);
		m_store.emplace(presetNumber, ptr);
		return ptr;
	}
}