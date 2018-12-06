#pragma once

#include "stdIncludes.h"

#include "SoundChunk.h"
#include "SoundChannel.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundPlayer : public SoundChannel {
	public:
		SoundPlayer(ChunkPtr chunk);
		~SoundPlayer() = default;

		void play(int plays = 1, int limitTimeMs = -1);
		bool tryPlay(int plays = 1, int limitTimeMs = -1);
		void replay(int plays = 1) { stop(); play(plays); }
		void pause();
		void resume();
		void stop(int delayTimeMs = 0);
		void cancelDelayedStop();

		void setVolume(double volumePercent);
		double getVolume();

		void setRawVolume(int rawVolume);
		int getRawVolume();

		ChunkPtr chunk();

	private:
		ChunkPtr m_chunk;
	};

	using SoundPlayerPtr = std::unique_ptr<SoundPlayer>;
}