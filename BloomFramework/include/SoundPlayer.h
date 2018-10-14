#pragma once
#include "stdIncludes.h"
#include "SoundChunk.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundPlayer {
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
		inline static int m_nextChannel = 0;
	};
}