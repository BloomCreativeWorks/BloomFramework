#pragma once

#include "stdIncludes.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API Music {
	public:
		Music() {}
		Music(std::string fileName);
		~Music();

		void load(std::string fileName);
		void play(int plays = 1, int fadeIn = 0);
		void pause();
		void resume();
		void rewind();
		void stop(int fadeOut = 0);

	private:
		Mix_Music * m_track = nullptr;
	};

	using TrackPtr = std::shared_ptr<Music>;
}