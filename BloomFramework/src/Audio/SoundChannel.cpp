#include "Audio/SoundChannel.h"
#include "Exception.h"

namespace bloom::audio {
	bool SoundChannel::s_state = false;
	int SoundChannel::s_adjustment = 0;
	unsigned SoundChannel::s_playingCounter = 0;
	std::vector<SoundChannel*> SoundChannel::s_channels{ MIX_CHANNELS, nullptr};
	SoundChannel::Mode SoundChannel::s_mode{ SoundChannel::Mode::Auto };

	SoundChannel::SoundChannel() {
		if (s_mode == Mode::Auto)
			++s_adjustment;
	}

	SoundChannel::~SoundChannel() {
		if (!isNull())
			s_channels[m_channel] = nullptr;
		if (s_mode == Mode::Auto)
			--s_adjustment;
	}

	void SoundChannel::assign(int channel) {
		if (static_cast<size_t>(channel) >= s_channels.size() || channel < 0)
			throw Exception{ "[SoundChannel] assignment failed" };
		else {
			if (!s_state)
				activate();
			m_channel = channel;
			s_channels[m_channel] = this;
			++s_playingCounter;
		}
	}

	void SoundChannel::activate() {
		Mix_ChannelFinished(_playback_finished);
		s_state = true;
	}

	bool SoundChannel::deactivate() {
		if (s_playingCounter)
			return false;
		Mix_ChannelFinished(nullptr);
		s_state = false;
		return true;
	}

	void SoundChannel::reallocate(int newQuantity) {
		if (s_mode == Mode::Manual)
			_reallocate_intl(newQuantity);
	}

	void SoundChannel::_reallocate_intl(int newQnt) {
		if (newQnt < 0)
			newQnt = 0;
		Mix_AllocateChannels(newQnt);
		s_channels.resize(newQnt);
	}

	int SoundChannel::allocated() {
		return Mix_AllocateChannels(-1);
	}

	void SoundChannel::setMode(Mode mode) {
		if (mode != s_mode)
			s_adjustment = 0;
		s_mode = mode;
	}

	bool SoundChannel::reserve() {
		if (s_mode == Mode::Manual)
			return false;
		if (auto allocChannels = allocated(); allocChannels == s_playingCounter && s_adjustment <= 0) {
			if (s_adjustment > 0) {
				_reallocate_intl(allocChannels + s_adjustment + 1);
				s_adjustment = -1;
			}
			else {
				_reallocate_intl(allocChannels + 1);
				--s_adjustment;
			}
			return true;
		}
		else {
			if (s_adjustment && allocChannels + s_adjustment > static_cast<int>(s_playingCounter))
				adjust();
			return false;
		}
	}

	void SoundChannel::adjust() {
		if (s_mode == Mode::Manual || !s_adjustment)
			return;
		if (s_adjustment > 0) {
			_reallocate_intl(allocated() + s_adjustment);
			s_adjustment = 0;
		}
		else {
			auto allocChannels = allocated();
			if (s_adjustment < -allocChannels)
				s_adjustment = -allocChannels;
			auto oldAdjustment = s_adjustment;
			auto cIt = s_channels.crbegin(), cBegIt = s_channels.crend();
			while (cIt != cBegIt && !(*cIt) && s_adjustment < 0) {
				++s_adjustment;
				++cIt;
			}
			_reallocate_intl(allocChannels - (s_adjustment - oldAdjustment));
		}
	}

	void SoundChannel::_playback_finished(int channel) {
		if (static_cast<size_t>(channel) >= s_channels.size())
			return;
		if (s_channels[channel]) {
			if (s_playingCounter)
				--s_playingCounter;
			s_channels[channel]->m_channel = NULL_CHANNEL;
			s_channels[channel] = nullptr;
		}
	}
}