// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SoundFX.h"
#include "Exception.h"

namespace bloom {
	SoundFX::SoundFX(std::string fileName, int channel) {
		m_channel = channel;
		load(fileName);
	}

	SoundFX::~SoundFX() {
		Mix_FreeChunk(m_chunk);
	}

	void SoundFX::load(std::string fileName) {
		m_chunk = Mix_LoadWAV(fileName.c_str());

		if (m_chunk == nullptr)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void SoundFX::play(int loops) {
		if (m_chunk == nullptr) {
			throw Exception("[SDL_Mixer] there is no file to play chunk");
		}

		if (Mix_PlayChannel(m_channel, m_chunk, loops) == -1)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void SoundFX::pause() {
		if (Mix_Paused(m_channel) == 0)
			Mix_Pause(m_channel);
		else
			Mix_Resume(m_channel);
	}

	void SoundFX::resume() {
		if (Mix_Paused(m_channel) != 0)
			Mix_Resume(m_channel);
		else
			Mix_Pause(m_channel);
	}

	void SoundFX::stop() {
		Mix_HaltChannel(m_channel);
	}
}