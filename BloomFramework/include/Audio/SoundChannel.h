#pragma once

#include <vector>
#include <stack>
#include "stdIncludes.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API SoundChannel {
	public:
		SoundChannel(SoundChannel * objThisPtr);
		~SoundChannel();

		static void optimize();

	protected:
		int m_channel;

	private:
		static std::vector<SoundChannel*> s_channels;
		static std::stack<int> s_freeChannels;
	};
}