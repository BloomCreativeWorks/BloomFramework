#pragma once

#include "Exception.h"
#include "MusicStore.h"
#include "MusicQueue.h"
#include "SoundChunk.h"
#include "SoundStore.h"
#include "SoundPlayer.h"
#include "SoundChannel.h"
#include "AudioDefine.h"

namespace bloom::audio {
	class Music {
	public:
		Music();

		MusicStore	store;
		MusicQueue	queue;

		void push(const std::filesystem::path & filePath, int plays = 1, bool ignoreInfinitePlayback = false, int fadeInMs = 0) {
			queue.add(store.load(filePath), plays, ignoreInfinitePlayback, fadeInMs);
		}

		void clear() {
			queue.clear(true);
			store.unloadAll();
		}

		static bool isPlaying() {
			return (MusicTrack::isPlaying());
		}

		static bool isPaused() {
			return (MusicTrack::isPaused());
		}

	private:
		static size_t obj_qnt;
	};

	Music::Music() {
		if (obj_qnt > 0)
			throw Exception("Creating more than 1 object of a `MusicFull` class is forbidden!");
		obj_qnt++;
	}

	size_t Music::obj_qnt = 0;


	class Sounds {
	public:
		Sounds();

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
		static size_t obj_qnt;
	};

	Sounds::Sounds() {
		if (obj_qnt > 1)
			throw Exception("Creating more than 1 object of a `SoundFull` class is forbidden!");
		obj_qnt++;
	}

	size_t Sounds::obj_qnt = 0;


	Music music;
	Sounds sounds;

	using MusicFull = Music;
	using SoundFull = Sounds;
}