#include "Audio/SoundPlayer.h"
#include "Exception.h"

namespace bloom::audio {
	SoundPlayer::SoundPlayer(ChunkPtr chunk) :
		SoundChannel(this),
		m_chunk(chunk)
	{}

	SoundPlayer::SoundPlayer(SoundPlayer&& other) :
		SoundChannel(this)
	{
		m_chunk.swap(other.m_chunk);
		other.m_chunk = nullptr;
	}

	SoundPlayer& SoundPlayer::operator=(SoundPlayer&& other) {
		m_chunk.swap(other.m_chunk);
		other.m_chunk = nullptr;
		return *this;
	}

	void SoundPlayer::play(int plays, int limitTimeMs) {
		if (Mix_Playing(m_channel))
			stop();

		plays = plays <= 0 ? -1 : (plays - 1);

		if (Mix_PlayChannelTimed(m_channel, m_chunk->m_chunk, plays, limitTimeMs) == -1)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	bool SoundPlayer::tryPlay(int plays, int limitTimeMs) {
		if (Mix_Playing(m_channel))
			return false;

		plays = plays <= 0 ? -1 : (plays - 1);

		if (Mix_PlayChannelTimed(m_channel, m_chunk->m_chunk, plays, limitTimeMs) == -1)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
		return true;
	}

	void SoundPlayer::pause() noexcept {
		if (!Mix_Paused(m_channel))
			Mix_Pause(m_channel);
		else
			Mix_Resume(m_channel);
	}

	void SoundPlayer::resume() noexcept {
		if (Mix_Paused(m_channel))
			Mix_Resume(m_channel);
		else
			Mix_Pause(m_channel);
	}

	void SoundPlayer::stop(int delayTimeMs) noexcept {
		if (delayTimeMs <= 0)
			Mix_HaltChannel(m_channel);
		else
			Mix_ExpireChannel(m_channel, delayTimeMs);
	}

	void SoundPlayer::cancelDelayedStop() noexcept {
		Mix_ExpireChannel(m_channel, -1);
	}

	void SoundPlayer::setRawVolume(int rawVolume) noexcept {
		if (rawVolume < 0)
			rawVolume = 0;
		else if (rawVolume > MIX_MAX_VOLUME)
			rawVolume = MIX_MAX_VOLUME;
		Mix_VolumeChunk(m_chunk->m_chunk, rawVolume);
	}

	void SoundPlayer::setVolume(double volumePercent) noexcept {
		if (volumePercent < std::numeric_limits<double>::epsilon())
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