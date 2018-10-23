#pragma once

#include "stdIncludes.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundPlayer;

	class SoundChunk {
		friend class SoundPlayer;
	public:
		SoundChunk(const std::filesystem::path & filePath);
		~SoundChunk();

	private:
		Mix_Chunk * m_chunk = nullptr;
	};

	using SoundChunkPtr = std::shared_ptr<SoundChunk>;
}