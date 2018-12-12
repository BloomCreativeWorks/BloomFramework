#pragma once

#include "stdIncludes.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundPlayer;

	class BLOOMFRAMEWORK_API SoundChunk {
		friend class SoundPlayer;

	public:
		SoundChunk(const std::filesystem::path& filePath);
		SoundChunk(const SoundChunk&) = delete;
		SoundChunk(SoundChunk&& other) noexcept;
		SoundChunk& operator=(const SoundChunk&) = delete;
		SoundChunk& operator=(SoundChunk&& other) noexcept;
		~SoundChunk();

		bool operator==(const SoundChunk& other) const noexcept;
		bool operator!=(const SoundChunk& other) const noexcept;

	private:
		Mix_Chunk* m_chunk = nullptr;
	};

	using ChunkPtr = std::shared_ptr<SoundChunk>;
}