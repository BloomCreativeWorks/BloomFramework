#pragma once
#include "stdIncludes.h"
#include "Font.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API FontStore {
	public:
		FontStore() = default;

		FontPtr load(const std::filesystem::path & filePath, const std::string & presetName, FontStyle style = defaultFontStyle);
		FontPtr find(const std::string & presetName)  const noexcept;
		void unload(const std::string & presetName);

		FontPtr operator[](const std::string & key) const noexcept;

	private:
		std::unordered_map<std::string, FontPtr>	m_store;
	};
}


