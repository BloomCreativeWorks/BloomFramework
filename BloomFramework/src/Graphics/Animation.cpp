#include "Graphics/Animation.h"

namespace bloom::graphics {
	Sprite Animation::update(double deltaTime) {
		std::clog << "Last update time: " << m_lastUpdateTime << std::endl; // Debugging stuff
		m_lastUpdateTime += deltaTime; // This does not seem to affect `Animation::m_lastUpdateTime`,
																	 // it seems to implicitly create a blank copy every time this function is called.
		std::clog << "New update time: " << m_lastUpdateTime << std::endl; // Debugging stuff
		std::clog << "Frame before: " << m_currentFrame << std::endl; // Debugging stuff
		if (m_lastUpdateTime > m_frameTime) {
			m_currentFrame += static_cast<int>(m_lastUpdateTime / m_frameTime);
			m_currentFrame %= animationFrames.size();
			m_lastUpdateTime = std::fmod(m_lastUpdateTime, m_frameTime);
		}
		std::clog << "Frame after: " << m_currentFrame << std::endl; // Debugging stuff
		return animationFrames[m_currentFrame];
	}
	
	void Animation::stop() {
		m_currentFrame = 0;
		m_lastUpdateTime = 0.0; // TODO: use 0.0 instead of 0
	}
	
	void Animation::setFPS(double fps) {
		m_frameTime = (1000.0 / fps); // TODO: use 1000.0 instead of 1000
	}
	
	void Animation::setFrameTime(double miliseconds) {
		m_frameTime = miliseconds;
	}
}