#pragma once
#include <vector>
#include "MusicStore.h"
#include "MusicQueue.h"
#include "SoundChunk.h"
#include "SoundStore.h"
#include "SoundPlayer.h"
#include "AudioDefine.h"

namespace bloom::audio {
	class MusicFull {
	public:
		MusicFull();

		MusicStore	store;
		MusicQueue	queue;

		void clear() {
			queue.clear();
			store.unloadAll();
		}

	private:
		inline static size_t obj_qnt = 0;
	};

	MusicFull::MusicFull() {
		if (obj_qnt > 0)
			throw Exception("Creating more than 1 object of a `MusicFull` class is forbidden!");
		obj_qnt++;
	}

	class SoundFull {
	public:
		SoundFull() {
			if (obj_qnt > 1)
				throw Exception("Creating more than 1 object of a `MusicFull` class is forbidden!");
			obj_qnt++;
		}

		int add(const std::string & filePath) {
			players.emplace_back(std::make_unique<SoundPlayer>(store.load(filePath)));
			return (static_cast<int>(players.size()) - 1);
		}

		void clear() {
			players.clear();
			store.unloadAll();
			SoundPlayer::channels.clear();
			SoundPlayer::free_channels = 0;
			Mix_AllocateChannels(0);
		}

		SoundStore store;
		std::vector<SoundPlayerPtr> players;

	private:
		inline static size_t obj_qnt = 0;
	};

	MusicFull music;
	SoundFull sounds;
}