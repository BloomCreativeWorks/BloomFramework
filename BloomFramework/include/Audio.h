#pragma once
#include "MusicStore.h"
#include "MusicQueue.h"
#include "SoundFX.h"
#include "SoundFXStore.h"

#define BLOOM_AUDIO_INFINITE_REPEAT -1

namespace bloom {
	class MusicFull : public MusicStore, public MusicQueue {
	public:
		MusicFull() {
			launch();
		}

		~MusicFull() {
			exit();
		}
	};

	MusicFull music = MusicFull();

	SoundFX sounds;
}