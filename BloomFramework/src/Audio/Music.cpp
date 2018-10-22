#include "Audio/Music.h"
#include "Exception.h"

namespace bloom::audio {
	Music::Music(std::string fileName) {
		load(fileName);
	}

	Music::~Music() {
		stop();
		Mix_FreeMusic(m_track);
		m_track = nullptr;
	}

	void Music::load(std::string fileName) {
		if (m_track)
			Mix_FreeMusic(m_track);
		m_track = Mix_LoadMUS(fileName.c_str());

		if (m_track == nullptr)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void Music::play(int plays, int fadeIn) {
		fadeIn = fadeIn < 0 ? fadeIn * -1 : fadeIn;
		if (m_track == nullptr) {
			throw Exception("[SDL_Mixer] there is no file to play track");
		}

		if (fadeIn > 0) {
			if (Mix_FadeInMusic(m_track, plays, fadeIn) == -1)
				throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
		}
		else {
			if (Mix_PlayMusic(m_track, plays) == -1)
				throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
		}
	}

	void Music::pause() {
		if (Mix_PausedMusic() == 0)
			Mix_PauseMusic();
		else
			Mix_ResumeMusic();
	}

	void Music::resume() {
		if (Mix_PausedMusic() != 0)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}

	void Music::rewind() {
		Mix_RewindMusic();
	}

	void Music::stop(int fadeOut) {
		fadeOut = fadeOut < 0 ? fadeOut * -1 : fadeOut;
		if (fadeOut > 0)
			Mix_FadeOutMusic(fadeOut);
		else
			Mix_HaltMusic();
	}
}