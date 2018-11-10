#include "Audio/SoundChunk.h"
#include "Exception.h"

namespace bloom::audio {
	SoundChunk::SoundChunk(const std::filesystem::path & filePath, bool ignoreChecks) {
		if (!ignoreChecks) {
			if (!std::filesystem::exists(filePath)) {
				throw Exception("[SoundChunk] " + filePath.u8string() + " not exists");
			}

			if (filePath.extension() != std::filesystem::path(L".wav"))
				throw Exception("[SoundChunk] non-wav file provided, use wav files only");
		}

		m_chunk = Mix_LoadWAV(filePath.u8string().c_str());
		if (m_chunk == nullptr)
			throw Exception("[SoundChunk -> SDL_Mixer] " + std::string(SDL_GetError()));
	}

	SoundChunk::~SoundChunk() {
		Mix_FreeChunk(m_chunk);
	}
}