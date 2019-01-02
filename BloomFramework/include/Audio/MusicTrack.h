#pragma once

#include "stdIncludes.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicTrack {
	public:
		MusicTrack() = delete;
		MusicTrack(const std::filesystem::path& filePath);
		MusicTrack(const MusicTrack&) = delete;
		MusicTrack(MusicTrack&&) = delete;
		MusicTrack& operator=(const MusicTrack&) = delete;
		MusicTrack& operator=(MusicTrack&&) = delete;
		~MusicTrack();

		void play(int plays = 1, int fadeIn = 0);
		bool tryPlay(int plays = 1, int fadeIn = 0);

		bool operator==(const MusicTrack& other) const noexcept;
		bool operator!=(const MusicTrack& other) const noexcept;

		static void pause() noexcept;
		static void resume() noexcept;
		static void rewind() noexcept;
		static void stop(int fadeOutMs = 0) noexcept;

		/// <summary>Checks if ANY track is playing now</summary>
		static bool isPlaying() noexcept;
		/// <sumary>Checks if ANY track is paused now</summary>
		static bool isPaused() noexcept;
		/// <sumary>Checks if ANY track is fading out now</summary>
		static Mix_Fading isFading() noexcept; /// TODO: rework this, make own enum

	private:
		Mix_Music* m_track;
	};

	using Track = MusicTrack;
	using TrackPtr = std::shared_ptr<MusicTrack>;

	struct TrackExt { TrackPtr track; int plays; int fadeInMs; bool bypassInfinitePlayback; };
}