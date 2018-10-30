#pragma once

#include <queue>
#include "MusicTrack.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicQueue {
		struct TrackExt { TrackPtr track; int plays; bool bypassInfinitePlayback; int fadeIn = 0; int fadeOut = 0; };

	public:
		MusicQueue();
		~MusicQueue();

		void activate();
		void add(TrackPtr track, int plays = 1, bool bypassInfinitePlayback = false, int fadeInMs = 0, int fadeOutMs = 0);
		void add(TrackExt track);
		void play(bool bypassFade = false);
		void pause();
		void resume();
		void rewind();
		void skip(bool bypassFade = false);
		void eject(bool bypassFade = true);
		void clear(bool bypassFade = false);
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
		static MusicQueue * m_thisObjectPtr;
	};
}