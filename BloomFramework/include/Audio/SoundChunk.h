#pragma once

#include "stdIncludes.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundPlayer;

	class BLOOMFRAMEWORK_API SoundChunk {
		friend class SoundPlayer;

	public:
		SoundChunk(const std::filesystem::path & filePath, bool ignoreChecks = false);
		~SoundChunk();

	private:
		Mix_Chunk * m_chunk = nullptr;
	};

	using SoundChunkPtr = std::shared_ptr<SoundChunk>;
}