#pragma once

#include "stdIncludes.h"

#include <vector>

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundChannel {
	public:
		enum class Mode {
			Auto,
			Manual
		};

		SoundChannel();
		SoundChannel(const SoundChannel&) = delete;
		SoundChannel(SoundChannel&&) = delete;
		SoundChannel& operator=(const SoundChannel&) = delete;
		SoundChannel& operator=(SoundChannel&&) = delete;
		~SoundChannel();

		bool isNull() const noexcept { return m_channel < 0; }
		void assign(int channel);

		static void activate();
		static bool deactivate();

		static void reallocate(int newQuantity);
		static int allocated();
		static void setMode(Mode mode);
		static Mode mode() noexcept { return s_mode; }
		static bool reserve();
		static void adjust();

		static bool isActive() noexcept { return s_state; }

		int operator()() const noexcept { return m_channel; };

	private:
		int m_channel = NULL_CHANNEL;

		static void _reallocate_intl(int newQnt);
		static void _playback_finished(int channel);

		static bool s_state;
		static int s_adjustment;
		static std::vector<SoundChannel*> s_channels;
		static unsigned s_playingCounter;
		static Mode s_mode;

		static constexpr int NULL_CHANNEL = -1;
	};
}