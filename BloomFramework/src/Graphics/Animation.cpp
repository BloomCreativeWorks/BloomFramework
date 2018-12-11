#include "Graphics/Animation.h"

namespace bloom::graphics {
	Sprite Animation::update(double deltaTime) {
		m_lastUpdateTime += deltaTime;
		if (m_lastUpdateTime > m_frameTime) {
			m_currentFrame = (m_currentFrame + static_cast<int>(m_lastUpdateTime / m_frameTime)) % animationFrames.size();
			m_lastUpdateTime = std::fmod(m_lastUpdateTime, m_frameTime);
		}
		return animationFrames[m_currentFrame];
	}
	
	void Animation::stop() {
		m_currentFrame = 0;
		m_lastUpdateTime = 0.0;
	}
	
	void Animation::setFPS(double fps) {
		m_frameTime = (1000.0 / fps);
	}
	
	void Animation::setFrameTime(double miliseconds) {
		m_frameTime = miliseconds;
	}
}