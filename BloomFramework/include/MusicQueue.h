#pragma once

#include <queue>
#include "Music.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicQueue {
		struct Track { TrackPtr track; int plays; bool ignoreInfinitePlayback; int fadeIn = 0; int fadeOut = 0; };
	public:
		MusicQueue();
		~MusicQueue();

		void launch();
		void add(TrackPtr track, int plays = 1, bool ignoreInfinitePlayback = false, int fadeIn = 0, int fadeOut = 0);
		void add(Track track);
		void remove(bool bypassFade = false);
		void play(bool bypassFade = false);
		void pause();
		void resume();
		void rewind();
		void skip(bool bypassFade = false);
		void clear(bool bypassFade = false);
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