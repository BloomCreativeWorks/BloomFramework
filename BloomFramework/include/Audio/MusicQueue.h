#pragma once

#include "stdIncludes.h"

#include <queue>
#include "MusicTrack.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicQueue {
	public:
		MusicQueue() = default;
		MusicQueue(const MusicQueue&) = delete;
		MusicQueue(MusicQueue&&) = delete;
		MusicQueue& operator=(const MusicQueue&) = delete;
		MusicQueue& operator=(MusicQueue&&) = delete;
		~MusicQueue();

		bool tryActivate() noexcept;
		void activate() noexcept;
		void add(TrackPtr track, int plays = 1, int fadeInMs = 0, bool bypassInfinitePlayback = false);
		void add(TrackExt track);
		void play(bool bypassFade = false);
		void pause();
		void resume();
		void rewind();
		void skip(int fadeOutMs = 0, bool allowUnpause = true);
		void eject(int fadeOutMs = 0);
		void clear(int fadeOutMs = 0);
		void deactivate(bool forced = false) noexcept;

		static void setVolume(double volumePercent) noexcept;
		static double getVolume() noexcept;

		static void setRawVolume(int rawVolume) noexcept;
		static int getRawVolume() noexcept;

		void setInfinitePlayback(bool state) noexcept;
		bool isInfinitePlayback() const noexcept;

		bool isActive() const noexcept;
		bool isPlaying() const noexcept;
		bool isPaused() const noexcept;

	private:
		std::queue<TrackExt> m_queue;
		bool m_infinitePlayback = true;
		bool m_playbackState = false;
		bool m_pauseState = false;

		static void _next_track();
		static void _finalize();
		static MusicQueue* s_currentQueuePtr;
	};
}