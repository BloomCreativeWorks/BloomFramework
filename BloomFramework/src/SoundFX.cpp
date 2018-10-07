#include "SoundFX.h"
#include "Exception.h"

#define BLOOM_AUDIO_INFINITE_REPEAT -1

namespace bloom {
	SoundFX::SoundFX(bool useAutoChannels) : m_autochannels(useAutoChannels) {
		if (m_autochannels)
			Mix_ChannelFinished(SoundFX::_finished);
		else
			Mix_ChannelFinished(nullptr);
	}

	SoundFX::SoundFX(std::string fileName, bool useAutoChannels) : m_autochannels(useAutoChannels) {
		load(fileName);
		if (m_autochannels)
			Mix_ChannelFinished(SoundFX::_finished);
		else
			Mix_ChannelFinished(nullptr);
	}

	SoundFX::~SoundFX() {
		Mix_FreeChunk(m_chunk);
	}

	void SoundFX::load(std::string fileName) {
		if (m_chunk) 
			Mix_FreeChunk(m_chunk);
		m_chunk = Mix_LoadWAV(fileName.c_str());

		if (m_chunk == nullptr)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void SoundFX::play(int plays) {
		if (m_chunk == nullptr) {
			throw Exception("[SDL_Mixer] there is no file to play chunk");
		}

		if (plays != BLOOM_AUDIO_INFINITE_REPEAT)
			--plays;

		if (m_autochannels)
			_add_channel();

		if (m_channel = Mix_PlayChannel(-1, m_chunk, plays); m_channel == -1)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void SoundFX::pause() {
		if (m_channel >= 0) {
			if (Mix_Paused(m_channel) == 0)
				Mix_Pause(m_channel);
			else
				Mix_Resume(m_channel);
		}
	}

	void SoundFX::resume() {
		if (m_channel >= 0) {
			if (Mix_Paused(m_channel) != 0)
				Mix_Resume(m_channel);
			else
				Mix_Pause(m_channel);
		}
	}

	void SoundFX::stop() {
		if (m_channel >= 0) {
			Mix_HaltChannel(m_channel);
		}
	}

	void SoundFX::setVolume(int volume) {
		if (volume < 0) volume *= -1;
		Mix_VolumeChunk(m_chunk, volume);
	}

	int SoundFX::getVolume() {
		return Mix_VolumeChunk(m_chunk, -1);
	}

	void SoundFX::_finished(int) {
		Mix_AllocateChannels(Mix_AllocateChannels(-1) - 1);
	}

	void SoundFX::_add_channel() {
		Mix_AllocateChannels(Mix_AllocateChannels(-1) + 1);
	}
}