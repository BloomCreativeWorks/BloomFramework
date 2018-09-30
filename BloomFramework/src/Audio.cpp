#include "Audio.h"
#include "Exception.h"

namespace bloom {
	BackgroundMusic::BackgroundMusic(std::string fileName) {
		load(fileName);
	}

	BackgroundMusic::~BackgroundMusic() {
		stop();
		Mix_FreeMusic(m_track);
		m_track = nullptr;
	}

	void BackgroundMusic::load(std::string fileName) {
		m_track = Mix_LoadMUS(fileName.c_str());

		if (m_track == NULL)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void BackgroundMusic::play(int plays) {
		if (m_track == NULL or m_track == nullptr) {
			throw Exception("[SDL_Mixer] there is no file to play track");
		}

		if (Mix_PlayMusic(m_track, plays) == -1)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void BackgroundMusic::pause() {
		if (Mix_PausedMusic() == 0)
			Mix_PauseMusic();
		else
			Mix_ResumeMusic();
	}

	void BackgroundMusic::resume() {
		if (Mix_PausedMusic() != 0)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}

	void BackgroundMusic::stop() {
		Mix_HaltMusic();
	}



	SoundEffects::SoundEffects(std::string fileName, int channel) {
		m_channel = channel;
		load(fileName);
	}

	SoundEffects::~SoundEffects() {
		Mix_FreeChunk(m_chunk);
	}

	void SoundEffects::load(std::string fileName) {
		m_chunk = Mix_LoadWAV(fileName.c_str());

		if (m_chunk == NULL)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void SoundEffects::play(int loops) {
		if (m_chunk == NULL or m_chunk == nullptr) {
			throw Exception("[SDL_Mixer] there is no file to play chunk");
		}

		if (Mix_PlayChannel(m_channel, m_chunk, loops) == -1)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void SoundEffects::pause() {
		if (Mix_Paused(m_channel) == 0)
			Mix_Pause(m_channel);
		else
			Mix_Resume(m_channel);
	}

	void SoundEffects::resume() {
		if (Mix_Paused(m_channel) != 0)
			Mix_Resume(m_channel);
		else
			Mix_Pause(m_channel);
	}

	void SoundEffects::stop() {
		Mix_HaltChannel(m_channel);
	}
}