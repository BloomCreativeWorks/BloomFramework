#pragma once

#include <unordered_map>
#include "stdIncludes.h"
#include "SoundChunk.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundStore {
	public:
		SoundChunkPtr load(const std::filesystem::path & filePath);
		SoundChunkPtr find(const std::filesystem::path & filePath);
		SoundChunkPtr find(std::nothrow_t, const std::filesystem::path & filePath) noexcept;
		void unload(const std::filesystem::path & filePath);
		void unloadAll();

	private:
		std::unordered_map<std::string, SoundChunkPtr> m_store;
	};
}