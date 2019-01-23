#include "Audio/SoundPlayer.h"
#include "Exception.h"

namespace bloom::audio {
	SoundPlayer::SoundPlayer(ChunkPtr chunk) :
		m_chunk(chunk)
	{}

	void SoundPlayer::play(int plays, int limitTimeMs) {
		if (!m_channel.isNull())
			stop();

		plays = (plays <= 0 ? -1 : (plays - 1));

		m_channel.reserve();
		if (auto channel = Mix_PlayChannelTimed(-1, m_chunk->m_chunk, plays, limitTimeMs); channel == -1)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
		else
			m_channel.assign(channel);
	}

	bool SoundPlayer::tryPlay(int plays, int limitTimeMs) {
		if (!m_channel.isNull())
			return false;

		plays = (plays <= 0 ? -1 : (plays - 1));

		m_channel.reserve();
		if (auto channel = Mix_PlayChannelTimed(-1, m_chunk->m_chunk, plays, limitTimeMs); channel == -1)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
		else
			m_channel.assign(channel);
		return true;
	}

	void SoundPlayer::pause() noexcept {
		if (!m_channel.isNull())
			return;
		Mix_Pause(m_channel());
		m_pauseFlag = true;
	}

	void SoundPlayer::resume() noexcept {
		if (!m_channel.isNull())
			return;
		Mix_Resume(m_channel());
		m_pauseFlag = false;
	}

	void SoundPlayer::stop(int delayTimeMs) noexcept {
		if (!m_channel.isNull())
			return;
		if (delayTimeMs <= 0)
			Mix_HaltChannel(m_channel());
		else
			Mix_ExpireChannel(m_channel(), delayTimeMs);
	}

	void SoundPlayer::cancelDelayedStop() noexcept {
		if (!m_channel.isNull())
			return;
		Mix_ExpireChannel(m_channel(), -1);
	}

	void SoundPlayer::setRawVolume(int rawVolume) noexcept {
		if (rawVolume < 0)
			rawVolume = 0;
		else if (rawVolume > MIX_MAX_VOLUME)
			rawVolume = MIX_MAX_VOLUME;
		Mix_VolumeChunk(m_chunk->m_chunk, rawVolume);
	}

	void SoundPlayer::setVolume(double volumePercent) noexcept {
		if (volumePercent < 0.0)
			volumePercent = 0.0;
		else if (volumePercent > 100.0)
			volumePercent = 100.0;
		Mix_VolumeChunk(m_chunk->m_chunk, static_cast<int>((static_cast<double>(MIX_MAX_VOLUME) / 100.0) * volumePercent));
	}

	double SoundPlayer::getVolume() noexcept {
		return (static_cast<double>(Mix_VolumeChunk(m_chunk->m_chunk, -1)) * 100.0) / static_cast<double>(MIX_MAX_VOLUME);
	}

	int SoundPlayer::getRawVolume() noexcept {
		return Mix_VolumeChunk(m_chunk->m_chunk, -1);
	}

	ChunkPtr SoundPlayer::chunk() noexcept {
		return m_chunk;
	}
}