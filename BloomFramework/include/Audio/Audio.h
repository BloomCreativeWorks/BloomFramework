#pragma once

#include "MusicStore.h"
#include "MusicQueue.h"
#include "SoundStore.h"
#include "SoundPlayer.h"

namespace bloom::audio {
	class Music {
	public:
		Music() : m_intlStore{ std::make_shared<MusicStore>() }, store{ *m_intlStore } {}
		explicit Music(MusicStore& existingStore) : m_intlStore{ nullptr }, store { existingStore } {}

		void pushBack(const std::filesystem::path& filePath, int plays = 1, int fadeInMs = 0, bool ignoreInfinitePlayback = false) {
			queue.pushBack(store.load(filePath), plays, fadeInMs, ignoreInfinitePlayback);
		}

		void pushFront(const std::filesystem::path& filePath, int plays = 1, int fadeInMs = 0, bool ignoreInfinitePlayback = false) {
			queue.pushFront(store.load(filePath), plays, fadeInMs, ignoreInfinitePlayback);
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

	private:
		std::shared_ptr<MusicStore> m_intlStore;

	public:
		MusicStore& store;
		MusicQueue queue;
	};

	class Sounds {
	public:
		Sounds() : m_intlStore{ std::make_shared<SoundStore>() }, store{ *m_intlStore } {}
		explicit Sounds(SoundStore& existingStore) : m_intlStore{ nullptr }, store{ existingStore } {}

		int add(const std::filesystem::path& filePath) {
			players.emplace_back(std::make_unique<SoundPlayer>(store.load(filePath)));
			return static_cast<int>(players.size()) - 1;
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
		}

		SoundPlayerPtr& operator[](size_t off) {
			return players[off];
		}

	private:
		std::shared_ptr<SoundStore> m_intlStore;

	public:
		SoundStore& store;
		std::vector<SoundPlayerPtr> players;
	};
}