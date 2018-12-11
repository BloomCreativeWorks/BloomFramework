#pragma once

#include "stdIncludes.h"

#include "SoundChunk.h"
#include "SoundChannel.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundPlayer : public SoundChannel {
	public:
		SoundPlayer(ChunkPtr chunk);
		SoundPlayer(const SoundPlayer&) = delete;
		SoundPlayer(SoundPlayer&& other) noexcept;
		SoundPlayer& operator=(const SoundPlayer&) = delete;
		SoundPlayer& operator=(SoundPlayer&& other) noexcept;
		~SoundPlayer() = default;

		void play(int plays = 1, int limitTimeMs = -1);
		bool tryPlay(int plays = 1, int limitTimeMs = -1);
		void replay(int plays = 1) { stop(); play(plays); }
		void pause() noexcept;
		void resume() noexcept;
		void stop(int delayTimeMs = 0) noexcept;
		void cancelDelayedStop() noexcept;

		void setVolume(double volumePercent) noexcept;
		double getVolume() noexcept;

		void setRawVolume(int rawVolume) noexcept;
		int getRawVolume() noexcept;

		ChunkPtr chunk() noexcept;

	private:
		ChunkPtr m_chunk;
	};

	using SoundPlayerPtr = std::unique_ptr<SoundPlayer>;
}