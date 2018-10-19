#include "MusicQueue.h"
#include "Exception.h"

namespace bloom::audio {
	MusicQueue * MusicQueue::m_thisObjectPtr = nullptr;
	size_t MusicQueue::obj_qnt = 0;

	MusicQueue::MusicQueue() {
		if (obj_qnt > 0)
			throw Exception("Creating more than 1 object of a `MusicFull` class is forbidden!");
		obj_qnt++;
	}

	MusicQueue::~MusicQueue() {
		clear();
	}

	void MusicQueue::launch() {
		m_thisObjectPtr = this;
		Mix_HookMusicFinished(MusicQueue::next_track);
	}

	void MusicQueue::add(TrackPtr track, int plays, bool ignoreInfinitePlayback, int fadeIn, int fadeOut) {
		m_queue.push({ track, plays, ignoreInfinitePlayback, fadeIn, fadeOut });
	}

	void MusicQueue::add(Track track) {
		m_queue.push(track);
	}

	void MusicQueue::remove(bool bypassFade) {
		if (!m_queue.empty()) {
			exit();
			if (m_queue.front().fadeOut > 0 && !bypassFade)
				m_queue.front().track->stop(m_queue.front().fadeOut);
			else
				m_queue.front().track->stop();
			m_queue.pop();
			launch();
			if (!m_queue.empty())
				play();
		}
	}

	void MusicQueue::play(bool bypassFade) {
		if (m_queue.empty())
			throw Exception("[MusicStore] store is empty");
		if (m_thisObjectPtr != this)
			launch();
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
		if(m_queue.front().fadeOut > 0 && !bypassFade)
			m_queue.front().track->stop(m_queue.front().fadeOut);
		else
			m_queue.front().track->stop();
		
	}

	void MusicQueue::clear(bool bypassFade) {
		exit();
		if (m_queue.size() != 0) {
			if(m_queue.front().fadeOut > 0 && !bypassFade)
				m_queue.front().track->stop(m_queue.front().fadeOut);
			else
				m_queue.front().track->stop();
			m_queue = std::queue<Track>();
		}
	}

	void MusicQueue::exit() {
		Mix_HookMusicFinished(nullptr);
	}

	void MusicQueue::setVolume(int volumePercent) {
		if (volumePercent < 0) volumePercent *= -1;
		if (volumePercent > 100) volumePercent = 100;
		double actualVolume = (static_cast<double>(MIX_MAX_VOLUME) / 100) * volumePercent;
		Mix_VolumeMusic(static_cast<int>(actualVolume));
	}

	void MusicQueue::setVolume(double volumePercent) {
		if (volumePercent < 0) volumePercent *= -1;
		if (volumePercent > 100) volumePercent = 100;
		double actualVolume = (static_cast<double>(MIX_MAX_VOLUME) / 100) * volumePercent;
		Mix_VolumeMusic(static_cast<int>(actualVolume));
	}

	double MusicQueue::getVolume() {
		double volumePercent = (static_cast<double>(Mix_VolumeMusic(-1)) / MIX_MAX_VOLUME) * 100;
		return volumePercent;
	}

	void MusicQueue::setInfinitePlayback(bool value) {
		m_infinitePlayback = value;
	}

	bool MusicQueue::isInfinitePlayback() {
		return m_infinitePlayback;
	}

	void MusicQueue::next_track() {
		if (m_thisObjectPtr) {
			if (!m_thisObjectPtr->m_queue.front().ignoreInfinitePlayback && m_thisObjectPtr->m_infinitePlayback) {
				m_thisObjectPtr->m_queue.push(m_thisObjectPtr->m_queue.front());
			}
			m_thisObjectPtr->m_queue.pop();

			if (!m_thisObjectPtr->m_queue.empty())
				m_thisObjectPtr->play();
		}
	}
}