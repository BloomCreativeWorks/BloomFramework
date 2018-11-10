#include "Audio/MusicQueue.h"
#include "Exception.h"

namespace bloom::audio {
	MusicQueue * MusicQueue::m_thisObjectPtr = nullptr;

	MusicQueue::MusicQueue() {
		Mix_HookMusicFinished(MusicQueue::next_track);
	}

	MusicQueue::~MusicQueue() {
		clear();
	}

	void MusicQueue::activate() {
		m_thisObjectPtr = this;
	}

	void MusicQueue::add(TrackPtr track, int plays, bool bypassInfinitePlayback, int fadeInMs, int fadeOutMs) {
		m_queue.push({ track, plays, bypassInfinitePlayback, fadeInMs, fadeOutMs });
	}

	void MusicQueue::add(TrackExt track) {
		m_queue.push(track);
	}

	void MusicQueue::play(bool bypassFade) {
		if (m_queue.empty())
			throw Exception("[MusicStore] store is empty");

		if (m_thisObjectPtr != this)
			activate();

		auto track = m_queue.front();
		if (track.fadeIn > 0 and !bypassFade)
			track.track->play(track.plays, track.fadeIn);
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

	void MusicQueue::skip(bool bypassFade) {
		if (m_queue.front().fadeOut > 0 && !bypassFade)
			m_queue.front().track->stop(m_queue.front().fadeOut);
		else
			m_queue.front().track->stop();
	}

	void MusicQueue::eject(bool bypassFade) {
		if (!m_queue.empty()) {
			m_queue.front().bypassInfinitePlayback = true;
			skip(bypassFade);
		}
	}

	void MusicQueue::clear(bool bypassFade) {
		deactivate();
		if (!m_queue.empty()) {
			if(m_queue.front().fadeOut > 0 && !bypassFade)
				m_queue.front().track->stop(m_queue.front().fadeOut);
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
		if (m_thisObjectPtr) {
			if (!m_thisObjectPtr->m_queue.front().bypassInfinitePlayback && m_thisObjectPtr->m_infinitePlayback) {
				m_thisObjectPtr->m_queue.push(m_thisObjectPtr->m_queue.front());
			}
			m_thisObjectPtr->m_queue.pop();

			if (!m_thisObjectPtr->m_queue.empty())
				m_thisObjectPtr->play();
		}
	}
}