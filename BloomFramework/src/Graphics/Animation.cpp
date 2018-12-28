#include "Graphics/Animation.h"
#include "Exception.h"

namespace bloom::graphics {
	Sprite Animation::update(double deltaTime) {
		if (animationFrames.empty())
			throw Exception("[Animation::update] there are no any frames");
		m_lastUpdateTime += std::fabs(deltaTime);
		if (m_lastUpdateTime > m_frameTime) {
			m_currentFrame = (m_currentFrame + static_cast<int>(m_lastUpdateTime / m_frameTime + 0.5)) % animationFrames.size();
			m_lastUpdateTime = std::fmod(m_lastUpdateTime, m_frameTime);
		}
		return animationFrames[m_currentFrame];
	}
}