#pragma once

#include <queue>
#include "Music.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicQueue {
		struct Track { TrackPtr track; int plays; bool bypassInfinitePlayback; int fadeIn = 0; int fadeOut = 0; };

	public:
		MusicQueue();
		~MusicQueue();

		void launch();
		void add(TrackPtr track, int plays = 1, bool bypassInfinitePlayback = false, int fadeInMs = 0, int fadeOutMs = 0);
		void add(Track track);
		void play(bool bypassFade = false);
		void pause();
		void resume();
		void rewind();
		void skip(bool bypassFade = false);
		void removeLast();
		void clear(bool bypassFade = false);
		void exit();
		void setRawVolume(int rawVolume);
		void setVolume(double volumePercent);
		double getVolume();
		int getRawVolume();
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