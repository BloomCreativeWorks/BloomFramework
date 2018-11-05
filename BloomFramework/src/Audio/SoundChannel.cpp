#include "Audio/SoundChannel.h"

namespace bloom::audio {
	std::vector<SoundChannel*> SoundChannel::channels;
	std::stack<int> SoundChannel::freeChannels;

	SoundChannel::SoundChannel(SoundChannel * objThisPtr) {
		if (!freeChannels.empty()) {
			m_channel = freeChannels.top();
			channels[m_channel] = objThisPtr;
			freeChannels.pop();
		}
		else {
			m_channel = static_cast<int>(channels.size());
			channels.push_back(objThisPtr);
			Mix_AllocateChannels(m_channel + 1);
		}
	}

	SoundChannel::~SoundChannel() {
		freeChannels.push(m_channel);
		channels[m_channel] = nullptr;
	}

	void SoundChannel::optimize() {
		int cs = static_cast<int>(channels.size()), fc;
		while (!freeChannels.empty()) {
			fc = freeChannels.top();
			if (fc >= cs) {
				freeChannels.pop();
			}
			else {
				if (channels.back() == nullptr) {
					--cs;
					channels.pop_back();
				}
				else {
					channels[fc] = channels.back();
					channels[fc]->m_channel = fc;
					channels.pop_back();
					--cs;
					freeChannels.pop();
				}
			}
		}

		Mix_AllocateChannels(cs);
	}
}