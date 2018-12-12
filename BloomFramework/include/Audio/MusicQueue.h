#pragma once

#include "stdIncludes.h"

#include <queue>
#include "MusicTrack.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicQueue {
	public:
		MusicQueue() noexcept;
		MusicQueue(const MusicQueue& other);
		MusicQueue(MusicQueue&& other);
		MusicQueue& operator=(const MusicQueue& other);
		MusicQueue& operator=(MusicQueue&& other);
		~MusicQueue();

		bool tryActivate() noexcept;
		void activate() noexcept;
		void add(TrackPtr track, int plays = 1, int fadeInMs = 0, bool bypassInfinitePlayback = false);
		void add(TrackExt track);
		void play(bool bypassFade = false);
		void pause();
		void resume();
		void rewind();
		void skip(int fadeOutMs = 0);
		void eject(int fadeOutMs = 0);
		void clear(int fadeOutMs = 0);
		void deactivate() noexcept;

		void setVolume(double volumePercent) noexcept;
		double getVolume() noexcept;

		void setRawVolume(int rawVolume) noexcept;
		int getRawVolume() noexcept;

		void setInfinitePlayback(bool value) noexcept;
		bool isInfinitePlayback() const noexcept;

	private:
		std::queue<TrackExt> m_queue;
		bool m_infinitePlayback = true;

		static void next_track();
		static MusicQueue* s_currentQueuePtr;
	};
}