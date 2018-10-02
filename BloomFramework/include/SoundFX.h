#pragma once
#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API SoundFX {
	public:
		SoundFX(int channel = -1) : m_channel(channel) {}
		SoundFX(std::string fileName, int channel = -1);
		~SoundFX();

		void load(std::string fileName);
		void play(int loops = 0);
		void pause();
		void resume();
		void stop();

	private:
		int m_channel;
		Mix_Chunk * m_chunk = nullptr;
	};

	using SoundFXPtr = std::shared_ptr<SoundFX>;
}