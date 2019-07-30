#include "Audio/MusicTrack.h"
#include "Exception.h"

namespace bloom::audio {
    MusicTrack::MusicTrack(const std::filesystem::path& filePath) {
        if (!std::filesystem::exists(filePath))
            throw Exception{ "MusicTrack::load", "File \"" + filePath.u8string() + "\" not exists" };

        m_track = Mix_LoadMUS(filePath.u8string().c_str());

        if (!m_track)
            throw Exception{ "MusicTrack::load", SDL_GetError() };
    }

    MusicTrack::~MusicTrack() {
        Mix_FreeMusic(m_track);
    }

    void MusicTrack::play(int plays, int fadeIn) {
        if (fadeIn < 0)
            fadeIn = 0;
        if (plays <= 0)
            plays = 0;

        if (Mix_FadeInMusic(m_track, plays, fadeIn) == -1)
            throw Exception{ "MusicTrack::play", SDL_GetError() };
    }

    bool MusicTrack::tryPlay(int plays, int fadeIn) {
        if (Mix_PlayingMusic())
            return false;
        play(plays, fadeIn);
        return true;
    }

    bool MusicTrack::operator==(const MusicTrack& other) const noexcept {
        return m_track == other.m_track;
    }

    bool MusicTrack::operator!=(const MusicTrack& other) const noexcept {
        return m_track != other.m_track;
    }

    void MusicTrack::pause() noexcept {
        if (!Mix_PausedMusic())
            Mix_PauseMusic();
        else
            Mix_ResumeMusic();
    }

    void MusicTrack::resume() noexcept {
        Mix_ResumeMusic();
    }

    void MusicTrack::rewind() noexcept {
        Mix_RewindMusic();
    }

    void MusicTrack::stop(int fadeOut) noexcept {
        fadeOut = fadeOut < 0 ? 0 : fadeOut;
        Mix_FadeOutMusic(fadeOut);
    }
}