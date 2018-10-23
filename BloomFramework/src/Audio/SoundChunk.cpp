#include "Audio/SoundChunk.h"
#include "Exception.h"

namespace bloom::audio {
	SoundChunk::SoundChunk(const std::filesystem::path & filePath) {
		if (!std::filesystem::exists(filePath)) {
			throw Exception("[SoundChunk] " + filePath.u8string() + " not exists");
		}

		m_chunk = Mix_LoadWAV(filePath.u8string().c_str());
		if (m_chunk == nullptr)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	SoundChunk::~SoundChunk() {
		Mix_FreeChunk(m_chunk);
	}
}