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
		void skip();
		void clear();
		void exit();
		void setInfinitePlayback(bool value);
		bool isInfinitePlayback();

	private:
		static void next_track();
		static MusicQueue* m_currentObjectPtr;

		MusicQueue* m_oldObjectPtr = nullptr;
		std::queue<Track> m_queue;
		bool m_infinitePlayback = true;
	};
}