#include "Audio/MusicTrack.h"
#include "Exception.h"

namespace bloom::audio {
	MusicTrack::MusicTrack(const std::filesystem::path & filePath) {
		load(filePath);
	}

	MusicTrack::~MusicTrack() {
		Mix_FreeMusic(m_track);
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
		fadeIn = fadeIn < 0 ? 0 : fadeIn;

		if (m_track == nullptr) {
			throw Exception("[SDL_Mixer] there is no file to play track");
		}

		if (Mix_FadeInMusic(m_track, plays, fadeIn) == -1)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	bool MusicTrack::tryPlay(int plays, int fadeIn) {
		if (Mix_PlayingMusic()) {
			return false;
		}
		else {
			play(plays, fadeIn);
			return true;
		}
	}

	void MusicTrack::pause() {
		if (!Mix_PausedMusic())
			Mix_PauseMusic();
		else
			Mix_ResumeMusic();
	}

	void MusicTrack::resume() {
		if (Mix_PausedMusic())
			Mix_ResumeMusic();
	}

	void MusicTrack::rewind() {
		Mix_RewindMusic();
	}

	void MusicTrack::stop(int fadeOut) {
		fadeOut = fadeOut < 0 ? 0 : fadeOut;
		Mix_FadeOutMusic(fadeOut);
	}

	bool MusicTrack::isPlaying() {
		return (Mix_PlayingMusic());
	}

	bool MusicTrack::isPaused() {
		return (Mix_PausedMusic());
	}
}