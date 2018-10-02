#pragma once
#include <queue>
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

	class MusicStore;

	class BLOOMFRAMEWORK_API MusicStore {
		struct Track { BackgroundMusic* track; int plays; bool ignoreInfinitePlayback; };
	public:
		MusicStore(bool infinitePlayback = false);
		~MusicStore();
		void launch();
		void add(std::string fileName, int plays = 1, bool ignoreInfinitePlayback = false);
		void remove();
		void play();
		void pause();
		void resume();
		void skip();
		void clear();
		void exit();
		void setInfinitePlayback(bool value);
		bool isInfinitePlayback();

	private:
		static void next_track();
		static MusicStore* m_currentObjectPtr;

		MusicStore* m_oldObjectPtr = nullptr;
		std::queue<Track> m_store;
		bool m_infinitePlayback = true;
	};
}