#pragma once

#include "stdIncludes.h"

#include <vector>
#include <stack>

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundChannel {
	public:
		SoundChannel() = delete;
		SoundChannel(const SoundChannel&) = delete;
		SoundChannel(SoundChannel&&) = delete;
		SoundChannel& operator=(const SoundChannel&) = delete;
		SoundChannel& operator=(SoundChannel&&) = delete;
		~SoundChannel();

		int channel() const noexcept;

		static void optimize();

	protected:
		SoundChannel(SoundChannel* objectPtr);

	private:
		int m_channel;

		static std::vector<SoundChannel*> s_channels;
		static std::stack<int> s_freeChannels;
	};
}