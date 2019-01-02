#include "Audio/MusicQueue.h"
#include "Exception.h"

namespace bloom::audio {
	MusicQueue::~MusicQueue() {
		clear();
	}

	MusicQueue* MusicQueue::s_currentQueuePtr = nullptr;

	bool MusicQueue::tryActivate() noexcept {
		if (s_currentQueuePtr == this)
			return true;
		if (Mix_PlayingMusic())
			return false;
		activate();
		return true;
	}

	void MusicQueue::activate() noexcept {
		if (s_currentQueuePtr != this) {
			if (s_currentQueuePtr)
				s_currentQueuePtr->deactivate(true);
			s_currentQueuePtr = this;
			Mix_HookMusicFinished(MusicQueue::_next_track);
		}
	}

	void MusicQueue::add(TrackPtr track, int plays, int fadeInMs, bool bypassInfinitePlayback) {
		m_queue.push({ track, plays, fadeInMs, bypassInfinitePlayback });
	}

	void MusicQueue::add(TrackExt track) {
		m_queue.push(track);
	}

	void MusicQueue::play(bool bypassFade) {
		if (m_queue.empty())
			throw Exception("[MusicQueue] queue is empty");

		if (s_currentQueuePtr != this)
			activate();

		auto track{ m_queue.front() };
		if (!bypassFade)
			track.track->play(track.plays, track.fadeInMs);
		else
			track.track->play(track.plays);
		m_playbackState = true;
	}

	void MusicQueue::pause() {
		if (s_currentQueuePtr == this) {
			m_queue.front().track->pause();
			m_playbackState = false;
			m_pauseState = true;
		}
	}

	void MusicQueue::resume() {
		if (s_currentQueuePtr == this) {
			m_queue.front().track->resume();
			m_playbackState = true;
			m_pauseState = false;
		}
	}

	void MusicQueue::rewind() {
		m_queue.front().track->rewind();
	}

	void MusicQueue::skip(int fadeOutMs, bool allowUnpause) {
		if (allowUnpause && m_pauseState)
			resume();
		if (fadeOutMs > 0)
			m_queue.front().track->stop(fadeOutMs);
		else
			m_queue.front().track->stop();
	}

	void MusicQueue::eject(int fadeOutMs) {
		if (!m_queue.empty()) {
			m_queue.front().bypassInfinitePlayback = true;
			skip(fadeOutMs);
		}
	}

	void MusicQueue::clear(int fadeOutMs) {
		deactivate(false);
		if (!m_queue.empty()) {
			if (fadeOutMs > 0)
				m_queue.front().track->stop(fadeOutMs);
			else
				m_queue.front().track->stop();

			while (!m_queue.empty())
				m_queue.pop();
		}
	}

	void MusicQueue::deactivate(bool forced) noexcept {
		if (forced) {
			Mix_HookMusicFinished(nullptr);
			Mix_HaltMusic();
			m_playbackState = false;
			m_pauseState = false;
			s_currentQueuePtr = nullptr;
		}
		else
			Mix_HookMusicFinished(MusicQueue::_finalize);
	}

	void MusicQueue::setRawVolume(int rawVolume) noexcept {
		if (rawVolume < 0)
			rawVolume = 0;
		if (rawVolume > MIX_MAX_VOLUME)
			rawVolume = MIX_MAX_VOLUME;
		Mix_VolumeMusic(rawVolume);
	}

	int MusicQueue::getRawVolume() noexcept {
		return Mix_VolumeMusic(-1);
	}

	void MusicQueue::setVolume(double volumePercent) noexcept {
		if (volumePercent < 0.0)
			volumePercent = 0.0;
		if (volumePercent > 100.0)
			volumePercent = 100.0;
		Mix_VolumeMusic(static_cast<int>((static_cast<double>(MIX_MAX_VOLUME) / 100.0) * volumePercent));
	}

	double MusicQueue::getVolume() noexcept {
		return (static_cast<double>(Mix_VolumeMusic(-1)) / MIX_MAX_VOLUME) * 100.0;
	}

	void MusicQueue::setInfinitePlayback(bool state) noexcept {
		m_infinitePlayback = state;
	}

	bool MusicQueue::isInfinitePlayback() const noexcept {
		return m_infinitePlayback;
	}

	bool MusicQueue::isActive() const noexcept {
		return s_currentQueuePtr == this;
	}

	bool MusicQueue::isPlaying() const noexcept {
		return m_playbackState;
	}

	bool MusicQueue::isPaused() const noexcept {
		return m_pauseState;
	}

	void MusicQueue::_next_track() {
		if (s_currentQueuePtr) {
			if (!s_currentQueuePtr->m_queue.front().bypassInfinitePlayback && s_currentQueuePtr->m_infinitePlayback) {
				s_currentQueuePtr->m_queue.push(s_currentQueuePtr->m_queue.front());
			}
			s_currentQueuePtr->m_queue.pop();

			s_currentQueuePtr->m_pauseState = false;
			if (s_currentQueuePtr->m_queue.empty())
				s_currentQueuePtr->m_playbackState = false;
			else
				s_currentQueuePtr->play();
		}
	}

	void MusicQueue::_finalize() {
		if (s_currentQueuePtr) {
			s_currentQueuePtr->m_playbackState = false;
			s_currentQueuePtr->m_pauseState = false;
			Mix_HookMusicFinished(nullptr);
			s_currentQueuePtr = nullptr;
		}
	}
}