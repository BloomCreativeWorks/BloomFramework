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

		static bool isPlaying() noexcept {
			return Mix_PlayingMusic() && !isPaused();
		}

		static bool isPaused() noexcept {
			return Mix_PausedMusic();
		}

		static bool isPlayingOrPaused() noexcept {
			return Mix_PlayingMusic();
		}

		static Mix_Fading isFading() noexcept { // TODO: rework this, make own enum
			return Mix_FadingMusic();
		}

	private:
		Mix_Music* m_track;
	};

	using Track = MusicTrack;
	using TrackPtr = std::shared_ptr<MusicTrack>;

    struct TrackExt {
        TrackPtr track;
        int plays, fadeInMs;
        bool ignoreInfinitePlayback;

        TrackExt(TrackPtr track, int plays, int fadeInMs, bool ignoreInfinitePlayback) :
            track{ std::move(track) }, plays{ plays }, fadeInMs{ fadeInMs }, ignoreInfinitePlayback{ ignoreInfinitePlayback } {}
    };
}