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
	};

	struct SoundFull {
		SoundStore store;
		std::vector<SoundPlayer> players;
	};

	MusicFull music;
	SoundFull sounds;
}