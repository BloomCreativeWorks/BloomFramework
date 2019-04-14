#include "Graphics/Animation.h"
#include "Exception.h"

namespace bloom::graphics {
	Sprite Animation::update(uint64_t deltaTime) {
		if (animationFrames.empty())
			throw Exception{ "Animation::update", "There are no any frames" };
		m_lastUpdateTime += deltaTime;
		if (m_lastUpdateTime > m_frameTime) {
			m_currentFrame = (m_currentFrame + m_lastUpdateTime / m_frameTime) % animationFrames.size();
			m_lastUpdateTime = m_lastUpdateTime % m_frameTime;
		}
		return animationFrames[m_currentFrame];
	}
}