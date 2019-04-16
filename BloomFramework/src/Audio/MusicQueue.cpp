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
			Mix_HookMusicFinished(_next_track);
		}
	}

	void MusicQueue::pushBack(TrackPtr track, int plays, int fadeInMs, bool bypassInfinitePlayback) {
		m_queue.push_back({ track, plays, fadeInMs, bypassInfinitePlayback });
	}

	void MusicQueue::pushBack(TrackExt&& track) {
		m_queue.push_back(std::forward<TrackExt>(track));
	}

	void MusicQueue::pushFront(TrackPtr track, int plays, int fadeInMs, bool bypassInfinitePlayback) {
		m_queue.push_front({ track, plays, fadeInMs, bypassInfinitePlayback });
	}

	void MusicQueue::pushFront(TrackExt&& track) {
		m_queue.push_front(std::forward<TrackExt>(track));
	}

	bool MusicQueue::play() {
		if (m_queue.empty())
			throw Exception("[MusicQueue] queue is empty");

		if (s_currentQueuePtr != this)
			activate();

		if (m_currentTrack.has_value())
			return false;

		m_currentTrack = std::move(m_queue.front());
		m_queue.pop_front();

		if (m_fadeIn)
			m_currentTrack->track->play(m_currentTrack->plays, m_currentTrack->fadeInMs);
		else
			m_currentTrack->track->play(m_currentTrack->plays);
		return m_playbackState = true;
	}

	void MusicQueue::replay() {
		m_currentTrack->track->play(m_currentTrack->plays, m_currentTrack->fadeInMs);
	}

	void MusicQueue::pause() {
		if (m_currentTrack.has_value()) {
			m_currentTrack->track->pause();
			m_playbackState = false;
			m_pauseState = true;
		}
	}

	void MusicQueue::resume() {
		if (m_currentTrack.has_value()) {
			m_currentTrack->track->resume();
			m_playbackState = true;
			m_pauseState = false;
		}
	}

	void MusicQueue::rewind() {
		if (m_currentTrack.has_value())
			m_currentTrack->track->rewind();
	}

	void MusicQueue::skip(int fadeOutMs, bool allowUnpause) {
		if (!m_currentTrack.has_value())
			return;
		if (allowUnpause && m_pauseState)
			resume();
		if (fadeOutMs > 0)
			m_currentTrack->track->stop(fadeOutMs);
		else
			m_currentTrack->track->stop();
	}

	void MusicQueue::eject(int fadeOutMs) {
		if (!m_currentTrack.has_value()) {
			m_currentTrack->ignoreInfinitePlayback = true;
			skip(fadeOutMs);
		}
	}

	void MusicQueue::clear(int fadeOutMs) {
		deactivate(false);
		if (m_currentTrack.has_value()) {
			if (fadeOutMs > 0)
				m_currentTrack->track->stop(fadeOutMs);
			else
				m_currentTrack->track->stop();

			m_currentTrack.reset();
			m_queue.clear();
		}
	}

	void MusicQueue::deactivate(bool forced) noexcept {
		if (forced) {
			_finalize();
			Mix_HaltMusic();
		}
		else
			Mix_HookMusicFinished(_finalize);
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

	void MusicQueue::_next_track() {
		if (s_currentQueuePtr) {
			if (!s_currentQueuePtr->m_currentTrack->ignoreInfinitePlayback && s_currentQueuePtr->m_infinitePlayback) {
				if (s_currentQueuePtr->m_queue.empty()) {
					s_currentQueuePtr->replay();
					return;
				}
				s_currentQueuePtr->m_queue.push_back(std::move(s_currentQueuePtr->m_currentTrack.value()));
			}
			s_currentQueuePtr->m_currentTrack.reset();

			s_currentQueuePtr->m_pauseState = false;
			if (s_currentQueuePtr->m_queue.empty())
				s_currentQueuePtr->m_playbackState = false;
			else
				s_currentQueuePtr->play();
		}
	}

	void MusicQueue::_finalize() {
		if (s_currentQueuePtr) {
			if (s_currentQueuePtr->m_currentTrack.has_value())
				s_currentQueuePtr->m_currentTrack.reset();
			s_currentQueuePtr->m_playbackState = s_currentQueuePtr->m_pauseState = false;
			Mix_HookMusicFinished(nullptr);
			s_currentQueuePtr = nullptr;
		}
	}
}