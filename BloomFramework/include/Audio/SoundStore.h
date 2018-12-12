#pragma once

#include "stdIncludes.h"

#include "SoundChunk.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundStore {
	public:
		ChunkPtr load(const std::filesystem::path& filePath);
		[[nodiscard]] ChunkPtr at(const std::filesystem::path& filePath) const;
		[[nodiscard]] ChunkPtr find(const std::filesystem::path& filePath) const noexcept;
		void unload(const std::filesystem::path& filePath);
		void unloadAll() noexcept;

		ChunkPtr operator[](const std::filesystem::path& key) const noexcept;

	private:
		std::unordered_map<std::string, ChunkPtr> m_store;
	};
}