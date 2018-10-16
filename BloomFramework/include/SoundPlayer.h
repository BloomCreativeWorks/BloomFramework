#pragma once

#include <vector>
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
		void pause();
		void resume();
		void stop();
		void setVolume(int volume);
		int getVolume();
		SoundChunkPtr chunk();

	private:
		SoundChunkPtr m_chunk;
		int m_channel;
		static std::vector<bool> channels;
		static int free_channels;
	};

	using SoundPlayerPtr = std::unique_ptr<SoundPlayer>;
}