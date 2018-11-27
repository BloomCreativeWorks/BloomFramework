#include "Audio/MusicQueue.h"
#include "Exception.h"

namespace bloom::audio {
	MusicQueue * MusicQueue::s_currentQueuePtr = nullptr;

	MusicQueue::MusicQueue() {
		Mix_HookMusicFinished(MusicQueue::next_track);
	}

	MusicQueue::~MusicQueue() {
		clear();
	}

	bool MusicQueue::tryActivate() {
		if (Mix_PlayingMusic() && s_currentQueuePtr != this) {
			return false;
		}
		else {
			activate();
			return true;
		}
	}

	void MusicQueue::activate() {
		if (s_currentQueuePtr != this) {
			Mix_HaltMusic();
			s_currentQueuePtr = this;
		}
	}

	void MusicQueue::add(TrackPtr track, int plays, bool bypassInfinitePlayback, int fadeInMs) {
		m_queue.push({ track, plays, bypassInfinitePlayback, fadeInMs });
	}

	void MusicQueue::add(TrackExt track) {
		m_queue.push(track);
	}

	void MusicQueue::play(bool bypassFade) {
		if (m_queue.empty())
			throw Exception("[MusicStore] store is empty");

		if (s_currentQueuePtr != this)
			activate();

		auto track = m_queue.front();
		if (track.fadeInMs > 0 and !bypassFade)
			track.track->play(track.plays, track.fadeInMs);
		else
			track.track->play(track.plays);
	}

	void MusicQueue::pause() {
		m_queue.front().track->pause();
	}

	void MusicQueue::resume() {
		m_queue.front().track->resume();
	}

	void MusicQueue::rewind() {
		m_queue.front().track->rewind();
	}

	void MusicQueue::skip(int fadeOutMs) {
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
		deactivate();
		if (!m_queue.empty()) {
			if (fadeOutMs > 0)
				m_queue.front().track->stop(fadeOutMs);
			else
				m_queue.front().track->stop();
			m_queue = std::queue<TrackExt>();
		}
	}

	void MusicQueue::deactivate() {
		Mix_HookMusicFinished(nullptr);
	}

	void MusicQueue::setRawVolume(int rawVolume) {
		if (rawVolume < 0) rawVolume = 0;
		if (rawVolume > MIX_MAX_VOLUME) rawVolume = MIX_MAX_VOLUME;
		Mix_VolumeMusic(rawVolume);
	}

	void MusicQueue::setVolume(double volumePercent) {
		if (volumePercent < std::numeric_limits<double>::epsilon()) volumePercent = 0.0;
		if (volumePercent > 100.0) volumePercent = 100.0;
		Mix_VolumeMusic(static_cast<int>((static_cast<double>(MIX_MAX_VOLUME) / 100.0) * volumePercent));
	}

	double MusicQueue::getVolume() {
		return (static_cast<double>(Mix_VolumeMusic(-1)) / MIX_MAX_VOLUME) * 100.0;
	}

	int MusicQueue::getRawVolume() {
		return Mix_VolumeMusic(-1);
	}

	void MusicQueue::setInfinitePlayback(bool value) {
		m_infinitePlayback = value;
	}

	bool MusicQueue::isInfinitePlayback() {
		return m_infinitePlayback;
	}

	void MusicQueue::next_track() {
		if (s_currentQueuePtr) {
			if (!s_currentQueuePtr->m_queue.front().bypassInfinitePlayback && s_currentQueuePtr->m_infinitePlayback) {
				s_currentQueuePtr->m_queue.push(s_currentQueuePtr->m_queue.front());
			}
			s_currentQueuePtr->m_queue.pop();

			if (!s_currentQueuePtr->m_queue.empty())
				s_currentQueuePtr->play();
		}
	}
}