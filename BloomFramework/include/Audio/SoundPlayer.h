#pragma once

#include <vector>
#include <stack>
#include "stdIncludes.h"
#include "SoundChunk.h"

namespace bloom::audio {
	class SoundFull;

	class BLOOMFRAMEWORK_API SoundPlayer {
		friend class SoundFull;
	public:
		SoundPlayer(SoundChunkPtr chunk);
		~SoundPlayer();

		void play(int plays = 1);
		void replay(int plays = 1) { stop(); play(plays); }
		void pause();
		void resume();
		void stop();
		void setRawVolume(int rawVolume);
		void setVolume(double volumePercent);
		double getVolume();
		int getRawVolume();
		SoundChunkPtr chunk();

		static void optimizeChannels();

	private:
		SoundChunkPtr m_chunk;
		int m_channel;

		static std::vector<SoundPlayer*> channels;
		static std::stack<int> freeChannels;
	};

	using SoundPlayerPtr = std::unique_ptr<SoundPlayer>;
}