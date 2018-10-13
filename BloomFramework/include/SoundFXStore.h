#pragma once
#include <unordered_map>
#include "stdIncludes.h"
#include "SoundFX.h"

namespace bloom {
	class BLOOMFRAMEWORK_API SoundFXStore {
	public:
		SoundChunkPtr load(const std::string & filePath);
		SoundChunkPtr find(const std::string & filePath);
		SoundChunkPtr find(std::nothrow_t, const std::string & filePath) noexcept;
		void unload(const std::string & filePath);
		void unload_all();

	private:
		std::unordered_map<std::string, SoundChunkPtr> m_store;
	};

	class BLOOMFRAMEWORK_API SoundControl {
	public:
		SoundControl(SoundChunkPtr chunk) : chunk(chunk), player(chunk) {}
		SoundChunkPtr chunk;
		SoundPlayer player;
	};
}