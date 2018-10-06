#pragma once
#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API SoundFX {
	public:
		SoundFX() : m_channel(-1) {}
		SoundFX(int channel) : m_channel(channel) {}
		SoundFX(std::string fileName, int channel = -1);
		~SoundFX();

		void load(std::string fileName);
		void play(int channel, int plays = 1);
		void play(int plays = 1);
		void pause();
		void resume();
		void stop();
		void setVolume(int volume);
		int getVolume();

	private:
		int m_channel;
		Mix_Chunk * m_chunk = nullptr;
	};

	using SoundFXPtr = std::shared_ptr<SoundFX>;
}