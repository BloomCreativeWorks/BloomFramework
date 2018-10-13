#pragma once
#include <vector>
#include "MusicStore.h"
#include "MusicQueue.h"
#include "SoundFX.h"
#include "SoundFXStore.h"

#define BLOOM_AUDIO_INFINITE_REPEAT -1

namespace bloom {
	class MusicFull {
	public:
		~MusicFull() {
			queue.exit();
		}

		MusicStore	store;
		MusicQueue	queue;
	};

	MusicFull music;
	SoundFXStore sounds_store;
	std::vector<SoundControl> sounds;
}