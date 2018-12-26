#pragma once
#include "stdIncludes.h"
#include "Font.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API FontStore {
	public:
		FontStore() = default;

		FontPtr load(const std::filesystem::path & filePath, size_t presetNumber, FontStyle style = defaultFontStyle);
		FontPtr find(size_t presetNumber) const noexcept;
		void unload(size_t presetNumber);
		void clear();

		FontPtr operator[](size_t key) const noexcept;

	private:
		std::unordered_map<size_t, FontPtr>	m_store;
	};
}


