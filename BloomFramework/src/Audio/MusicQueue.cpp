#include "Audio/MusicQueue.h"
#include "Exception.h"

namespace bloom::audio {
    MusicQueue::CurrentTrack MusicQueue::s_current{};

	MusicQueue::~MusicQueue() {
		clear();
	}

	bool MusicQueue::tryActivate() noexcept {
		if (s_current.queue == this)
			return true;
		if (Mix_PlayingMusic())
			return false;
		activate();
		return true;
	}

	void MusicQueue::activate() noexcept {
		if (s_current.queue != this) {
			if (s_current.queue)
				deactivate(true);
			s_current.queue = this;
			Mix_HookMusicFinished(_next_track);
		}
	}

	void MusicQueue::pushBack(TrackPtr track, int plays, int fadeInMs, bool bypassInfinitePlayback) {
		m_queue.emplace_back(std::move(track), plays, fadeInMs, bypassInfinitePlayback);
	}

	void MusicQueue::pushBack(TrackExt&& track) {
		m_queue.push_back(std::forward<TrackExt>(track));
	}

	void MusicQueue::pushFront(TrackPtr track, int plays, int fadeInMs, bool bypassInfinitePlayback) {
		m_queue.emplace_front(std::move(track), plays, fadeInMs, bypassInfinitePlayback);
	}

	void MusicQueue::pushFront(TrackExt&& track) {
		m_queue.push_front(std::forward<TrackExt>(track));
	}

	bool MusicQueue::play() {
		if (m_queue.empty())
			throw Exception{ "MusicQueue::play", "Queue is empty" };

		if (s_current.queue != this)
			activate();

		if (s_current.track.has_value())
			return false;

		s_current.track = std::move(m_queue.front());
		m_queue.pop_front();

		if (m_fadeIn)
			s_current.track->track->play(s_current.track->plays, s_current.track->fadeInMs);
		else
			s_current.track->track->play(s_current.track->plays);
		return m_playbackState = true;
	}

	void MusicQueue::replay() {
		s_current.track->track->play(s_current.track->plays, s_current.track->fadeInMs);
	}

	void MusicQueue::pause() {
		if (s_current.track.has_value()) {
			s_current.track->track->pause();
			m_playbackState = false;
			m_pauseState = true;
		}
	}

	void MusicQueue::resume() {
		if (s_current.track.has_value()) {
			s_current.track->track->resume();
			m_playbackState = true;
			m_pauseState = false;
		}
	}

	void MusicQueue::rewind() {
		if (s_current.track.has_value())
			s_current.track->track->rewind();
	}

	void MusicQueue::skip(int fadeOutMs, bool allowUnpause) {
		if (!s_current.track.has_value())
			return;
		if (allowUnpause && m_pauseState)
			resume();
		if (fadeOutMs > 0)
			s_current.track->track->stop(fadeOutMs);
		else
			s_current.track->track->stop();
	}

	void MusicQueue::eject(int fadeOutMs) {
		if (!s_current.track.has_value()) {
			s_current.track->ignoreInfinitePlayback = true;
			skip(fadeOutMs);
		}
	}

	void MusicQueue::clear(int fadeOutMs) {
		deactivate(false);
		if (s_current.track.has_value()) {
			if (fadeOutMs > 0)
				s_current.track->track->stop(fadeOutMs);
			else
				s_current.track->track->stop();

			s_current.track.reset();
			m_queue.clear();
		}
	}

	void MusicQueue::deactivate(bool forced) noexcept {
        Mix_HookMusicFinished(_finalize);
		if (forced)
			Mix_HaltMusic();			
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
		Mix_VolumeMusic(static_cast<int>(static_cast<double>(MIX_MAX_VOLUME) * volumePercent / 100.0));
	}

	double MusicQueue::getVolume() noexcept {
		return static_cast<double>(Mix_VolumeMusic(-1)) * 100.0 / MIX_MAX_VOLUME;
	}

	void MusicQueue::_next_track() {
		if (s_current.queue) {
			if (!s_current.track->ignoreInfinitePlayback && s_current.queue->m_infinitePlayback) {
				if (s_current.queue->m_queue.empty()) {
					s_current.queue->replay();
					return;
				}
				s_current.queue->m_queue.push_back(std::move(s_current.track.value()));
			}
			s_current.track.reset();

			s_current.queue->m_pauseState = false;
			if (s_current.queue->m_queue.empty())
				s_current.queue->m_playbackState = false;
			else
				s_current.queue->play();
		}
	}

	void MusicQueue::_finalize() {
		if (s_current.queue) {
			if (s_current.track.has_value())
				s_current.track.reset();
			s_current.queue->m_playbackState = s_current.queue->m_pauseState = false;
			Mix_HookMusicFinished(nullptr);
			s_current.queue = nullptr;
            s_current.track.reset();
		}
	}
}