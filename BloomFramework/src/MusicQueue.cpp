#include "MusicQueue.h"
#include "Exception.h"

namespace bloom::audio {
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

	void MusicQueue::add(TrackPtr track, int plays, bool ignoreInfinitePlayback) {
		m_queue.push({ track, plays, ignoreInfinitePlayback });
	}

	void MusicQueue::remove() {
		if (!m_queue.empty()) {
			exit();
			m_queue.front().track->stop();
			m_queue.pop();
			launch();
			if (!m_queue.empty())
				play();
		}
	}

	void MusicQueue::play() {
		if (m_queue.empty())
			throw Exception("[MusicStore] store is empty");
		if (m_thisObjectPtr != this)
			launch();
		auto track = m_queue.front();
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

	void MusicQueue::skip() {
		m_queue.front().track->stop();
	}

	void MusicQueue::clear() {
		exit();
		if (m_queue.size() != 0) {
			m_queue.front().track->stop();
			m_queue = std::queue<Track>();
		}
	}

	void MusicQueue::exit() {
		Mix_HookMusicFinished(nullptr);
	}

	void MusicQueue::setVolume(int volume) {
		if (volume < 0) volume *= -1;
		Mix_VolumeMusic(volume);
	}

	int MusicQueue::getVolume() {
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
			if (!m_thisObjectPtr->m_queue.front().ignoreInfinitePlayback && m_thisObjectPtr->m_infinitePlayback) {
				m_thisObjectPtr->m_queue.push(m_thisObjectPtr->m_queue.front());
			}
			m_thisObjectPtr->m_queue.pop();

			if (!m_thisObjectPtr->m_queue.empty())
				m_thisObjectPtr->play();
		}
	}
}