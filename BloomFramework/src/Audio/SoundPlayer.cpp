#include "Audio/SoundPlayer.h"
#include "Exception.h"
#include "Audio/AudioDefine.h"

namespace bloom::audio {
	SoundPlayer::SoundPlayer(SoundChunkPtr chunk) : SoundChannel(static_cast<SoundChannel*>(this)), m_chunk(chunk) {}

	void SoundPlayer::play(int plays, int limitTimeMs) {
		if (Mix_Playing(m_channel) != 0)
			return;

		if (plays != BLOOM_AUDIO_INFINITE_REPEAT)
			--plays;

		if (Mix_PlayChannelTimed(m_channel, m_chunk->m_chunk, plays, limitTimeMs) == -1)
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

	void SoundPlayer::stop(int delayTimeMs) {
		if (delayTimeMs <= 0)
			Mix_HaltChannel(m_channel);
		else
			Mix_ExpireChannel(m_channel, delayTimeMs);
	}

	void SoundPlayer::cancelDelayedStop() {
		Mix_ExpireChannel(m_channel, -1);
	}

	void SoundPlayer::setRawVolume(int rawVolume) {
		if (rawVolume < 0) rawVolume = 0;
		else if (rawVolume > MIX_MAX_VOLUME) rawVolume = MIX_MAX_VOLUME;
		Mix_VolumeChunk(m_chunk->m_chunk, rawVolume);
	}

	void SoundPlayer::setVolume(double volumePercent) {
		if (volumePercent < std::numeric_limits<double>::epsilon()) volumePercent = 0.0;
		else if (volumePercent > 100.0) volumePercent = 100.0;
		Mix_VolumeChunk(m_chunk->m_chunk, static_cast<int>((static_cast<double>(MIX_MAX_VOLUME) / 100.0) * volumePercent));
	}

	double SoundPlayer::getVolume() {
		return (static_cast<double>(Mix_VolumeChunk(m_chunk->m_chunk, -1)) * 100.0) / static_cast<double>(MIX_MAX_VOLUME);
	}

	int SoundPlayer::getRawVolume() {
		return Mix_VolumeChunk(m_chunk->m_chunk, -1);
	}

	SoundChunkPtr SoundPlayer::chunk() {
		return m_chunk;
	}
}