#include "Audio/SoundChannel.h"

namespace bloom::audio {
	std::vector<SoundChannel*> SoundChannel::s_channels;
	std::stack<int> SoundChannel::s_freeChannels;

	SoundChannel::SoundChannel(SoundChannel * objThisPtr) {
		if (!s_freeChannels.empty()) {
			m_channel = s_freeChannels.top();
			s_channels[m_channel] = objThisPtr;
			s_freeChannels.pop();
		}
		else {
			m_channel = static_cast<int>(s_channels.size());
			s_channels.push_back(objThisPtr);
			Mix_AllocateChannels(m_channel + 1);
		}
	}

	SoundChannel::~SoundChannel() {
		s_freeChannels.push(m_channel);
		s_channels[m_channel] = nullptr;
	}

	void SoundChannel::optimize() {
		int cs = static_cast<int>(s_channels.size());
		while (!s_freeChannels.empty()) {
			int fc = s_freeChannels.top();
			if (fc >= cs) {
				s_freeChannels.pop();
			}
			else {
				if (s_channels.back() == nullptr) {
					--cs;
					s_channels.pop_back();
				}
				else {
					s_channels[fc] = s_channels.back();
					Mix_HaltChannel(s_channels[fc]->m_channel);
					s_channels[fc]->m_channel = fc;
					s_channels.pop_back();
					--cs;
					s_freeChannels.pop();
				}
			}
		}

		Mix_AllocateChannels(cs);
	}
}