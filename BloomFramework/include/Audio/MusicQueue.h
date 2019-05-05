#pragma once

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
		void pushBack(TrackPtr track, int plays = 1, int fadeInMs = 0, bool bypassInfinitePlayback = false);
		void pushBack(TrackExt&& track);
		void pushFront(TrackPtr track, int plays = 1, int fadeInMs = 0, bool bypassInfinitePlayback = false);
		void pushFront(TrackExt&& track);
		bool play();
		void pause();
		void resume();
		void rewind();
		void skip(int fadeOutMs = 0, bool allowUnpause = true);
		void eject(int fadeOutMs = 0);
		void clear(int fadeOutMs = 0);

		static void deactivate(bool forced = false) noexcept;

		static void setVolume(double volumePercent) noexcept;
		static double getVolume() noexcept;

		static void setRawVolume(int rawVolume) noexcept;
		static int getRawVolume() noexcept;

		void setInfinitePlayback(bool state) noexcept {
			m_infinitePlayback = state;
		}

		bool isInfinitePlayback() const noexcept {
			return m_infinitePlayback;
		}

		void setFadeInPolicy(bool state) noexcept {
			m_fadeIn = state;
		}

		bool setFadeInPolicy() const noexcept {
			return m_fadeIn;
		}

		bool isActive() const noexcept {
			return s_currentQueuePtr == this;
		}

		bool isPlaying() const noexcept {
			return m_playbackState;
		}

		bool isPaused() const noexcept {
			return m_pauseState;
		}

	private:
		void replay();

		std::deque<TrackExt> m_queue;
		std::optional<TrackExt> m_currentTrack{};
		bool m_infinitePlayback{ true };
		bool m_playbackState{ false };
		bool m_pauseState{ false };
		bool m_fadeIn{ true };

		static void _next_track();
		static void _finalize();
		static MusicQueue* s_currentQueuePtr;
	};
}