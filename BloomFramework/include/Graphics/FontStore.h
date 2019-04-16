#pragma once
#include "stdIncludes.h"
#include "Font.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API FontStore {
	public:
		FontStore() = default;

		FontPtr load(const std::filesystem::path& filePath, size_t presetNumber, FontStyle style = FontStyle{});

		FontPtr find(size_t presetNumber) const noexcept {
			const auto fontIt = m_store.find(presetNumber);
			return fontIt != m_store.end() ? fontIt->second : FontPtr{};
		}

		void unload(size_t presetNumber) {
			m_store.erase(presetNumber);
		}

		void clear() noexcept {
			m_store.clear();
		}

		FontPtr operator[](size_t key) const noexcept {
			return find(key);
		}

	private:
		std::unordered_map<size_t, FontPtr>	m_store;
	};
}