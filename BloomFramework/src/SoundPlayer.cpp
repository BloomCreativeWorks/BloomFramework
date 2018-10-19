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

	void SoundPlayer::setRawVolume(int rawVolume) {
		if (rawVolume < 0) rawVolume = 0;
		if (rawVolume > MIX_MAX_VOLUME) rawVolume = MIX_MAX_VOLUME;
		Mix_VolumeMusic(rawVolume);
	}

	void SoundPlayer::setVolume(double volumePercent) {
		if (volumePercent < std::numeric_limits<double>::epsilon()) volumePercent = 0;
		if (volumePercent > 100.0) volumePercent = 100.0;
		Mix_VolumeChunk(m_chunk->m_chunk, static_cast<int>((static_cast<double>(MIX_MAX_VOLUME) / 100.0) * volumePercent));
	}

	double SoundPlayer::getVolume() {
		return (static_cast<double>(Mix_VolumeChunk(m_chunk->m_chunk, -1)) / MIX_MAX_VOLUME) * 100.0;
	}

	int SoundPlayer::getRawVolume() {
		return Mix_VolumeMusic(-1);
	}

	SoundChunkPtr SoundPlayer::chunk() {
		return m_chunk;
	}
}