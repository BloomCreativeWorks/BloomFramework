#pragma once

#include "stdIncludes.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicTrack {
	public:
		MusicTrack() = default;
		MusicTrack(const std::filesystem::path & filePath);
		MusicTrack(const MusicTrack&) = delete;
		MusicTrack(MusicTrack&& other) noexcept;
		MusicTrack& operator=(const MusicTrack&) = delete;
		MusicTrack& operator=(MusicTrack&& other) noexcept;
		~MusicTrack();

		void load(const std::filesystem::path & filePath);
		void play(int plays = 1, int fadeIn = 0);
		bool tryPlay(int plays = 1, int fadeIn = 0);

		bool operator==(const MusicTrack& other) const noexcept;
		bool operator!=(const MusicTrack& other) const noexcept;
		
		static void pause() noexcept;
		static void resume() noexcept;
		static void rewind() noexcept;
		void stop(int fadeOut = 0) noexcept;

		static bool isPlaying() noexcept;
		static bool isPaused() noexcept;

	private:
		Mix_Music* m_track = nullptr;
	};

	using Track = MusicTrack;
	using TrackPtr = std::shared_ptr<MusicTrack>;

	struct TrackExt { TrackPtr track; int plays; int fadeInMs; bool bypassInfinitePlayback; };
}