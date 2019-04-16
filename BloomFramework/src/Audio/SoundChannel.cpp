#include "Audio/SoundChannel.h"
#include "Exception.h"

inline auto allocated() {
	return Mix_AllocateChannels(-1);
}

inline auto playing() {
	return Mix_Playing(-1);
}

namespace bloom::audio {
	bool SoundChannel::s_state = false;
	int SoundChannel::s_adjustment = 0;
	std::vector<SoundChannel*> SoundChannel::s_channels{ MIX_CHANNELS, nullptr};

	SoundChannel::SoundChannel(bool needAlloc) : m_allocFlag{ needAlloc } {
		if (m_allocFlag)
			++s_adjustment;
	}

	SoundChannel::~SoundChannel() {
		if (isValid())
			s_channels[m_channel] = nullptr;
		if (m_allocFlag)
			--s_adjustment;
	}

	void SoundChannel::assign(int channel) {
		if (static_cast<size_t>(channel) >= s_channels.size() || channel < 0)
			throw Exception{ "SoundChannel", "channel assignment failed" };
		if (!s_state)
			activate();
		m_channel = channel;
		s_channels[m_channel] = this;
	}

	void SoundChannel::activate() {
		Mix_ChannelFinished(_playback_finished);
		s_state = true;
	}

	bool SoundChannel::deactivate() {
		if (playing())
			return false;
		Mix_ChannelFinished(nullptr);
		s_state = false;
		return true;
	}

	void SoundChannel::reallocate(int newQuantity) {
		if (newQuantity < 0)
			newQuantity = 0;
		Mix_AllocateChannels(newQuantity);
		s_channels.resize(newQuantity);
	}

	bool SoundChannel::reserve() {
		if (const auto allocatedChannels = allocated(); allocatedChannels == playing() && s_adjustment <= 0) {
			if (s_adjustment > 0) {
				reallocate(allocatedChannels + s_adjustment + 1);
				s_adjustment = -1;
			}
			else {
				reallocate(allocatedChannels + 1);
				--s_adjustment;
			}
			return true;
		}
		else {
			if (s_adjustment && allocatedChannels + s_adjustment > playing())
				adjust();
			return false;
		}
	}

	void SoundChannel::adjust() {
		if (!s_adjustment)
			return;
		if (s_adjustment > 0) {
			reallocate(allocated() + s_adjustment);
			s_adjustment = 0;
		}
		else {
			const auto allocChannels = allocated();
			if (s_adjustment < -allocChannels)
				s_adjustment = -allocChannels;
			const auto oldAdjustment = s_adjustment;
			auto cIt = s_channels.crbegin();
			const auto cEndIt = s_channels.crend();
			while (cIt != cEndIt && !(*cIt) && s_adjustment < 0) {
				++s_adjustment;
				++cIt;
			}
			reallocate(allocChannels - (s_adjustment - oldAdjustment));
			if (cIt == cEndIt)
				s_adjustment = 0;
		}
	}

	void SoundChannel::_playback_finished(int channel) {
		if (static_cast<size_t>(channel) >= s_channels.size())
			return;
		if (s_channels[channel]) {
			s_channels[channel]->m_channel = NULL_CHANNEL;
			s_channels[channel] = nullptr;
		}
	}
}