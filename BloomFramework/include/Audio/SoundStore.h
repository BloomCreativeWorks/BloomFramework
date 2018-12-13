#pragma once

#include "stdIncludes.h"

#include "SoundChunk.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundStore {
	public:
		ChunkPtr load(const std::filesystem::path& filePath);
		ChunkPtr at(const std::filesystem::path& filePath) const;
		ChunkPtr find(const std::filesystem::path& filePath) const noexcept;
		void unload(const std::filesystem::path& filePath);
		void unloadAll() noexcept;

		ChunkPtr operator[](const std::filesystem::path& key) const noexcept;

	private:
		std::unordered_map<std::filesystem::path, ChunkPtr> m_store;
	};
}