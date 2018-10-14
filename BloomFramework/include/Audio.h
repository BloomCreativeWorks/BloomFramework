#pragma once
#include <vector>
#include "MusicStore.h"
#include "MusicQueue.h"
#include "SoundChunk.h"
#include "SoundStore.h"
#include "SoundPlayer.h"
#include "AudioDefine.h"

namespace bloom::audio {
	struct MusicFull {
		MusicStore	store;
		MusicQueue	queue;

		void clear() {
			queue.clear();
			store.unloadAll();
		}
	};

	struct SoundFull {
		SoundStore store;
		std::vector<SoundPlayer> players;

		void clear() {
			players.clear();
			store.unloadAll();
		}
	};

	MusicFull music;
	SoundFull sounds;
}