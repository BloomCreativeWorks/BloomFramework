#pragma once

#include "Exception.h"
#include "MusicStore.h"
#include "MusicQueue.h"
#include "SoundChunk.h"
#include "SoundStore.h"
#include "SoundPlayer.h"
#include "SoundChannel.h"

namespace bloom::audio {
	class Music {
	public:
		static Music & instance();

		void push(const std::filesystem::path & filePath, int plays = 1, int fadeInMs = 0, bool ignoreInfinitePlayback = false) {
			queue.add(store.load(filePath), plays, fadeInMs, ignoreInfinitePlayback);
		}

		void clear() {
			queue.clear();
			store.unloadAll();
		}

		static bool isPlaying() {
			return MusicTrack::isPlaying();
		}

		static bool isPaused() {
			return MusicTrack::isPaused();
		}

		MusicStore store;
		MusicQueue queue;

	private:
		Music() = default;
		~Music() = default;
		Music(const Music &) = delete;
		Music(Music &&) = delete;
		Music& operator=(const Music &) = delete;
	};

	Music & Music::instance() {
		static Music music_instance;
		return music_instance;
	}


	class Sounds {
	public:
		static Sounds & instance();

		int add(const std::filesystem::path & filePath) {
			players.emplace_back(std::make_unique<SoundPlayer>(store.load(filePath)));
			return (static_cast<int>(players.size()) - 1);
		}

		void stopAll() {
			for (auto & p : players) {
				p->stop();
			}
		}

		void pauseAll() {
			for (auto & p : players) {
				p->pause();
			}
		}

		void resumeAll() {
			for (auto & p : players) {
				p->resume();
			}
		}

		void clear() {
			players.clear();
			store.unloadAll();
			SoundChannel::optimize();
		}

		void optimize() {
			SoundChannel::optimize();
		}

		SoundPlayerPtr & operator[](size_t off) {
			return players[off];
		}

		SoundStore store;
		std::vector<SoundPlayerPtr> players;

	private:
		Sounds() = default;
		~Sounds() = default;
		Sounds(const Sounds &) = delete;
		Sounds(Sounds &&) = delete;
		Sounds& operator=(const Sounds &) = delete;
	};

	Sounds & Sounds::instance() {
		static Sounds sounds_instance;
		return sounds_instance;
	}

	Music & music{ Music::instance() };
	Sounds & sounds{ Sounds::instance() };
}