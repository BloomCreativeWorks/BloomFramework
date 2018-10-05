#include "MusicQueue.h"
#include "Exception.h"

namespace bloom {
	void MusicQueue::launch() {
		m_oldObjectPtr = m_currentObjectPtr;
		m_currentObjectPtr = this;
		Mix_HookMusicFinished((void(*) ())(MusicQueue::next_track));
	}

	void MusicQueue::add(TrackPtr track, int plays, bool ignoreInfinitePlayback) {
		m_queue.push( { track, plays, ignoreInfinitePlayback } );
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
		if (m_currentObjectPtr != this)
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
		m_queue = std::queue<Track>();
	}

	void MusicQueue::exit() {
		if (m_currentObjectPtr == this) {
			m_currentObjectPtr = m_oldObjectPtr;
		}
		if (!m_currentObjectPtr)
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
		if (m_currentObjectPtr != nullptr) {
			if (!m_currentObjectPtr->m_queue.front().ignoreInfinitePlayback && m_currentObjectPtr->m_infinitePlayback) {
				m_currentObjectPtr->m_queue.push(m_currentObjectPtr->m_queue.front());
			}
			m_currentObjectPtr->m_queue.pop();

			if (!m_currentObjectPtr->m_queue.empty())
				m_currentObjectPtr->play();
		}
	}
}