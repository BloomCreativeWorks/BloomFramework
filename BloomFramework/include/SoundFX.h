#pragma once
#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API SoundFX {
	public:
		SoundFX();
		SoundFX(std::string fileName);
		~SoundFX();

		void load(std::string fileName);
		void play(int plays = 1);
		void pause();
		void resume();
		void stop();
		void setVolume(int volume);
		int getVolume();

	private:
		Mix_Chunk * m_chunk = nullptr;
		int m_channel = -1;

		static void _finished(int);
		static void _add_channel();
	};

	using SoundFXPtr = std::shared_ptr<SoundFX>;
}