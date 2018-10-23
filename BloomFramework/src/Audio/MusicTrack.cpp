#include "Audio/MusicTrack.h"
#include "Exception.h"

namespace bloom::audio {
	MusicTrack::MusicTrack(const std::filesystem::path & filePath) {
		load(filePath);
	}

	MusicTrack::~MusicTrack() {
		stop();
		Mix_FreeMusic(m_track);
		m_track = nullptr;
	}

	void MusicTrack::load(const std::filesystem::path & filePath) {
		if (!std::filesystem::exists(filePath)) {
			throw Exception("[MusicTrack::load] " + filePath.u8string() + " not exists");
		}

		if (m_track)
			Mix_FreeMusic(m_track);
		m_track = Mix_LoadMUS(filePath.u8string().c_str());

		if (m_track == nullptr)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void MusicTrack::play(int plays, int fadeIn) {
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

	void MusicTrack::pause() {
		if (Mix_PausedMusic() == 0)
			Mix_PauseMusic();
		else
			Mix_ResumeMusic();
	}

	void MusicTrack::resume() {
		if (Mix_PausedMusic() != 0)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}

	void MusicTrack::rewind() {
		Mix_RewindMusic();
	}

	void MusicTrack::stop(int fadeOut) {
		fadeOut = fadeOut < 0 ? fadeOut * -1 : fadeOut;
		if (fadeOut > 0)
			Mix_FadeOutMusic(fadeOut);
		else
			Mix_HaltMusic();
	}
}