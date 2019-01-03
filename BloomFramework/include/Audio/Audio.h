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
		void push(const std::filesystem::path& filePath, int plays = 1, int fadeInMs = 0, bool ignoreInfinitePlayback = false) {
			queue.add(store.load(filePath), plays, fadeInMs, ignoreInfinitePlayback);
		}

		void clear() {
			queue.clear();
		}

		bool isPlaying() const noexcept {
			return queue.isPlaying();
		}

		bool isPaused() const noexcept {
			return queue.isPaused();
		}

		static bool isAnyPlaying() noexcept {
			return MusicTrack::isPlaying();
		}

		static bool isAnyPaused() noexcept {
			return MusicTrack::isPaused();
		}

		MusicStore& store{ MusicStore::store() };
		MusicQueue queue;
	};

	class Sounds {
	public:
		int add(const std::filesystem::path& filePath) {
			players.emplace_back(std::make_unique<SoundPlayer>(store.load(filePath)));
			return (static_cast<int>(players.size()) - 1);
		}

		void stopAll() noexcept {
			for (auto& p : players) {
				p->stop();
			}
		}

		void pauseAll() noexcept {
			for (auto& p : players) {
				p->pause();
			}
		}

		void resumeAll() noexcept {
			for (auto& p : players) {
				p->resume();
			}
		}

		void clear() {
			players.clear();
			SoundChannel::optimize();
		}

		void optimize() {
			SoundChannel::optimize();
		}

		SoundPlayerPtr& operator[](size_t off) {
			return players[off];
		}

		SoundStore& store{ SoundStore::store() };
		std::vector<SoundPlayerPtr> players;
	};
}