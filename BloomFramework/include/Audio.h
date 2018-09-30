#pragma once
#include "stdIncludes.h"

#define BLOOM_AUDIO_LOOP -1

namespace bloom {
	class BLOOMFRAMEWORK_API BackgroundMusic {
	public:
		BackgroundMusic() {}
		BackgroundMusic(std::string fileName);
		~BackgroundMusic();

		void load(std::string fileName);
		void play(int plays = 1);
		void pause();
		void resume();
		void stop();

	private:
		Mix_Music * m_track = nullptr;
	};

	class BLOOMFRAMEWORK_API SoundEffects {
	public:
		SoundEffects(int channel = -1) : m_channel(channel) {}
		SoundEffects(std::string fileName, int channel = -1);
		~SoundEffects();

		void load(std::string fileName);
		void play(int loops = 0);
		void pause();
		void resume();
		void stop();

	private:
		int m_channel;
		Mix_Chunk * m_chunk = nullptr;
	};
}