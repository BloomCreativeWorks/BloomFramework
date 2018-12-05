#pragma once

#include <queue>
#include "MusicTrack.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicQueue {
	public:
		MusicQueue();
		~MusicQueue();

		bool tryActivate();
		void activate();
		void add(TrackPtr track, int plays = 1, bool bypassInfinitePlayback = false, int fadeInMs = 0);
		void add(TrackExt track);
		void play(bool bypassFade = false);
		void pause();
		void resume();
		void rewind();
		void skip(int fadeOutMs = 0);
		void eject(int fadeOutMs = 0);
		void clear(int fadeOutMs = 0);
		void deactivate();

		void setVolume(double volumePercent);
		double getVolume();

		void setRawVolume(int rawVolume);
		int getRawVolume();

		void setInfinitePlayback(bool value);
		bool isInfinitePlayback();

	private:
		std::queue<TrackExt> m_queue;
		bool m_infinitePlayback = true;

		static void next_track();
		static MusicQueue * s_currentQueuePtr;
	};
}