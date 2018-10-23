#pragma once

#include "stdIncludes.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicTrack {
	public:
		MusicTrack() {}
		MusicTrack(const std::filesystem::path & filePath);
		~MusicTrack();

		void load(const std::filesystem::path & filePath);
		void play(int plays = 1, int fadeIn = 0);
		void pause();
		void resume();
		void rewind();
		void stop(int fadeOut = 0);

	private:
		Mix_Music * m_track = nullptr;
	};

	using Track = MusicTrack;
	using TrackPtr = std::shared_ptr<MusicTrack>;
}