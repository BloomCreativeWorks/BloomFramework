#pragma once
#include <queue>
#include "Music.h"

namespace bloom {
	class BLOOMFRAMEWORK_API MusicQueue {
		struct Track { TrackPtr track; int plays; bool ignoreInfinitePlayback; };
	public:
		void launch();
		void add(TrackPtr track, int plays = 1, bool ignoreInfinitePlayback = false);
		void remove();
		void play();
		void pause();
		void resume();
		void rewind();
		void skip();
		void clear();
		void exit();
		void setVolume(int volume);
		int getVolume();
		void setInfinitePlayback(bool value);
		bool isInfinitePlayback();

	private:
		MusicQueue* m_oldObjectPtr = nullptr;
		std::queue<Track> m_queue;
		bool m_infinitePlayback = true;

		static void next_track();
		inline static MusicQueue* m_currentObjectPtr = nullptr;
	};
}