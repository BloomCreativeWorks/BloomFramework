#pragma once
#include "stdIncludes.h"
#include "SoundChunk.h"

namespace bloom::audio {
	struct SoundFull;

	class BLOOMFRAMEWORK_API SoundPlayer {
		friend struct SoundFull;
	public:
		SoundPlayer(SoundChunkPtr chunk);

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
		inline static int m_channelsQnt = 0;
	};
}