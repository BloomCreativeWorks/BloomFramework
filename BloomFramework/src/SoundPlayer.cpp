#include "SoundPlayer.h"
#include "Exception.h"
#include "AudioDefine.h"

namespace bloom::audio {
	std::vector<bool> SoundPlayer::channels = std::vector<bool>();
	int SoundPlayer::free_channels = 0;

	SoundPlayer::SoundPlayer(SoundChunkPtr chunk) : m_chunk(chunk), m_channel(static_cast<int>(channels.size())) {
		if (free_channels > 0) {
			for (size_t i = 0; i < channels.size(); ++i)
				if (channels[i] == false) {
					m_channel = static_cast<int>(i);
					channels[i] = true;
					free_channels--;
					break;
				}
		}
		else {
			channels.push_back(true);
			Mix_AllocateChannels(static_cast<int>(channels.size()));
		}
	}

	SoundPlayer::~SoundPlayer() {
		channels[m_channel] = false;
		free_channels++;
	}

	void SoundPlayer::play(int plays) {
		if (Mix_Playing(m_channel) != 0)
			return;

		if (plays != BLOOM_AUDIO_INFINITE_REPEAT)
			--plays;

		if (Mix_PlayChannel(m_channel, m_chunk->m_chunk, plays) == -1)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	void SoundPlayer::pause() {
		if (Mix_Paused(m_channel) == 0)
			Mix_Pause(m_channel);
		else
			Mix_Resume(m_channel);
	}

	void SoundPlayer::resume() {
		if (Mix_Paused(m_channel) != 0)
			Mix_Resume(m_channel);
		else
			Mix_Pause(m_channel);
	}

	void SoundPlayer::stop() {
		Mix_HaltChannel(m_channel);
	}

	void SoundPlayer::setVolume(int volume) {
		if (volume < 0) volume *= -1;
		Mix_VolumeChunk(m_chunk->m_chunk, volume);
	}

	int SoundPlayer::getVolume() {
		return Mix_VolumeChunk(m_chunk->m_chunk, -1);
	}

	SoundChunkPtr SoundPlayer::chunk() {
		return m_chunk;
	}
}