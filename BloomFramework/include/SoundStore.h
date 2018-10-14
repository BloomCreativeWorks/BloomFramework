#pragma once
#include <unordered_map>
#include "stdIncludes.h"
#include "SoundChunk.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundStore {
	public:
		~SoundStore();

		SoundChunkPtr load(const std::string & filePath);
		SoundChunkPtr find(const std::string & filePath);
		SoundChunkPtr find(std::nothrow_t, const std::string & filePath) noexcept;
		void unload(const std::string & filePath);
		void unloadAll();

	private:
		std::unordered_map<std::string, SoundChunkPtr> m_store;
	};
}