#pragma once
#include "stdIncludes.h"
#include <unordered_map>

namespace bloom {
	class BLOOMFRAMEWORK_API SoundPlayer;

	class SoundChunk {
		friend class SoundPlayer;
	public:
		SoundChunk(const std::string & filename);
		~SoundChunk();

	private:
		std::string m_filename;
		Mix_Chunk * m_chunk = nullptr;
	};

	using SoundChunkPtr = std::shared_ptr<SoundChunk>;

	class BLOOMFRAMEWORK_API SoundPlayer {
	public:
		SoundPlayer(SoundChunkPtr chunk);

		void play(int plays = 1);
		void pause();
		void resume();
		void stop();
		void setVolume(int volume);
		int getVolume();

	private:
		SoundChunkPtr m_chunk;
		int m_channel;
		inline static int m_nextChannel = 0;
	};
}