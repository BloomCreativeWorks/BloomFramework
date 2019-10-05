#include "Graphics/Animation.h"
#include "Exception.h"

namespace bloom::graphics {
	Sprite Animation::update(double deltaTime) {
		if (animationFrames.empty())
			throw Exception{ "Animation::update", "There are no any frames" };
		m_lastUpdateTime += deltaTime;
		if (m_lastUpdateTime > m_frameTime) {
			m_currentFrame = (m_currentFrame + static_cast<int>(m_lastUpdateTime / m_frameTime)) % animationFrames.size();
			m_lastUpdateTime = std::fmod(m_lastUpdateTime, m_frameTime);
		}
		return animationFrames[m_currentFrame];
	}
}