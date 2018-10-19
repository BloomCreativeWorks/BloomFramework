#include "Audio/SoundChunk.h"
#include "Exception.h"

namespace bloom::audio {
	SoundChunk::SoundChunk(const std::string & filename) : m_filename(filename) {
		m_chunk = Mix_LoadWAV(filename.c_str());
		if (m_chunk == nullptr)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	SoundChunk::~SoundChunk() {
		Mix_FreeChunk(m_chunk);
	}
}