#pragma once

#include "stdIncludes.h"

#include <vector>

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundChannel {
	public:
		SoundChannel(bool needAlloc = true);
		SoundChannel(const SoundChannel&) = delete;
		SoundChannel(SoundChannel&&) = delete;
		SoundChannel& operator=(const SoundChannel&) = delete;
		SoundChannel& operator=(SoundChannel&&) = delete;
		~SoundChannel();

		void assign(int channel);
		bool isValid() const noexcept { return m_channel >= 0; }

		static void activate();
		static bool deactivate();

		static bool reserve();
		static void adjust();

		static bool isActive() noexcept { return s_state; }

		int operator()() const noexcept { return m_channel; }
		operator int() const noexcept { return m_channel; }

	private:
		int m_channel = NULL_CHANNEL;
		bool m_allocFlag;

		static void reallocate(int newQuantity);

		static void _playback_finished(int channel);

		static bool s_state;
		static int s_adjustment;
		static std::vector<SoundChannel*> s_channels;

		static constexpr int NULL_CHANNEL = -1;
	};
}