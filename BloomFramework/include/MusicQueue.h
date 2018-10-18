#pragma once

#include <queue>
#include "Music.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicQueue {
		struct Track { TrackPtr track; int plays; bool ignoreInfinitePlayback; };
	public:
		MusicQueue();
		~MusicQueue();

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
		void setVolume(int volumePercent);
		void setVolume(double volumePercent);
		double getVolume();
		void setInfinitePlayback(bool value);
		bool isInfinitePlayback();

	private:
		std::queue<Track> m_queue;
		bool m_infinitePlayback = true;

		static void next_track();
		static MusicQueue * m_thisObjectPtr;
		static size_t obj_qnt;
	};
}