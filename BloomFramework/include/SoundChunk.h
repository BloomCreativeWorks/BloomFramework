#pragma once
#include "stdIncludes.h"
#include <unordered_map>

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundPlayer;

	class SoundChunk {
		friend class SoundPlayer;
	public:
		SoundChunk(const std::string & filename);
		~SoundChunk();

	private:
		std::string m_filename;
		Mix_Chunk * m_chunk = nullptr;
	};

	using SoundChunkPtr = std::shared_ptr<SoundChunk>;
}