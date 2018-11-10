#pragma once

#include <vector>
#include <stack>
#include "stdIncludes.h"
#include "SoundChunk.h"
#include "SoundChannel.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundPlayer : public SoundChannel {
	public:
		SoundPlayer(SoundChunkPtr chunk);
		~SoundPlayer() = default;

		void play(int plays = 1, int limitTimeMs = -1);
		void replay(int plays = 1) { stop(); play(plays); }
		void pause();
		void resume();
		void stop(int delayTimeMs = 0);
		void cancelDelayedStop();

		void setVolume(double volumePercent);
		double getVolume();

		void setRawVolume(int rawVolume);
		int getRawVolume();

		SoundChunkPtr chunk();

	private:
		SoundChunkPtr m_chunk;
	};

	using SoundPlayerPtr = std::unique_ptr<SoundPlayer>;
}