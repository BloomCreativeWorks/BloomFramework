#include "SoundFX.h"
#include "Exception.h"

#define BLOOM_AUDIO_INFINITE_REPEAT -1

namespace bloom {
	SoundChunk::SoundChunk(const std::string & filename) : m_filename(filename) {
		m_chunk = Mix_LoadWAV(filename.c_str());
		if (m_chunk == nullptr)
			throw Exception("[SDL_Mixer] " + std::string(SDL_GetError()));
	}

	SoundChunk::~SoundChunk() {
		Mix_FreeChunk(m_chunk);
	}


	SoundPlayer::SoundPlayer(SoundChunkPtr chunk) : m_chunk(chunk), m_channel(m_nextChannel) {
		m_nextChannel++;
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
}