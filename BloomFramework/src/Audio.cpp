#include "Audio.h"
#include "Exception.h"
#include <functional>

namespace bloom {
	MusicStore* MusicStore::m_currentObjectPtr = nullptr;


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



	MusicStore::MusicStore(bool infinitePlayback) : m_infinitePlayback(infinitePlayback) {}

	MusicStore::~MusicStore() {
		clear();
		exit();
	}

	void MusicStore::launch() {
		m_oldObjectPtr = m_currentObjectPtr;
		m_currentObjectPtr = this;
		Mix_HookMusicFinished((void(*) ())(MusicStore::next_track));
	}

	void MusicStore::add(std::string fileName, int plays) {
		m_store.push({ new BackgroundMusic(fileName) , plays });
	}

	void MusicStore::remove() {
		if (!m_store.empty()) {
			exit();
			m_store.front().first->stop();
			m_store.pop();
			launch();
			if (!m_store.empty())
				play();
		}
	}

	void MusicStore::play() {
		if (m_store.empty())
			throw Exception("[MusicStore] store is empty");
		if (m_currentObjectPtr != this)
			launch();
		auto track = m_store.front();
		track.first->play(track.second);
	}

	void MusicStore::pause() {
		m_store.front().first->pause();
	}

	void MusicStore::resume() {
		m_store.front().first->resume();
	}

	void MusicStore::skip() {
		m_store.front().first->stop();
	}

	void MusicStore::clear() {
		m_store = std::queue<Track>();
	}

	void MusicStore::exit() {
		if (m_currentObjectPtr == this) {
			m_currentObjectPtr = m_oldObjectPtr;
			Mix_HookMusicFinished((void(*) ())(MusicStore::next_track));
		}
	}

	void MusicStore::setInfinitePlayback(bool value) {
		m_infinitePlayback = value;
	}

	bool MusicStore::isInfinitePlayback() {
		return m_infinitePlayback;
	}

	void MusicStore::next_track() {
		if (m_currentObjectPtr != nullptr) {
			if (m_currentObjectPtr->m_infinitePlayback) {
				m_currentObjectPtr->m_store.push(m_currentObjectPtr->m_store.front());
			}
			m_currentObjectPtr->m_store.pop();

			if (!m_currentObjectPtr->m_store.empty())
				m_currentObjectPtr->play();
		}
	}
}