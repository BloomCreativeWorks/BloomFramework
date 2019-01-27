#pragma once

#include "stdIncludes.h"

#include "SoundChunk.h"
#include "SoundChannel.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundPlayer {
	public:
		SoundPlayer(ChunkPtr chunk, bool needAlloc = true);
		SoundPlayer(const SoundPlayer&) = delete;
		SoundPlayer(SoundPlayer&&) = delete;
		SoundPlayer& operator=(const SoundPlayer&) = delete;
		SoundPlayer& operator=(SoundPlayer&&) = delete;
		~SoundPlayer() = default;

		void play(int plays = 1, int limitTimeMs = -1);
		bool tryPlay(int plays = 1, int limitTimeMs = -1);
		void replay(int plays = 1) { stop(); play(plays); }
		void pause() noexcept;
		void resume() noexcept;
		void stop(int delayTimeMs = 0) noexcept;
		void cancelDelayedStop() noexcept;

		bool isPlaying() const noexcept { return (m_channel.isValid() && !m_pauseFlag); }
		bool isPaused() const noexcept { return (m_pauseFlag && m_channel.isValid()); }
		bool isPlayingOrPaused() const noexcept { return m_channel.isValid(); }

		void setVolume(double volumePercent) noexcept;
		double getVolume() noexcept;

		void setRawVolume(int rawVolume) noexcept;
		int getRawVolume() noexcept;

		ChunkPtr chunk() noexcept;

	private:
		ChunkPtr m_chunk;
		SoundChannel m_channel;
		bool m_pauseFlag = false;
	};

	using SoundPlayerPtr = std::shared_ptr<SoundPlayer>;
}