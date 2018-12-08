#pragma once
#include "stdIncludes.h"
#include "Sprite.h"


namespace bloom::graphics {
	class Animation {
	public:
		Sprite update(double deltaTime) {
			m_lastUpdateTime += deltaTime;
			if (m_lastUpdateTime / m_frameTime > 1) {
				m_currentFrame += static_cast<int>(m_lastUpdateTime / m_frameTime);
				m_currentFrame %= animationFrames.size();
				m_lastUpdateTime = std::fmod(m_lastUpdateTime, m_frameTime);
			}
			return animationFrames[m_currentFrame];
		}

		void stop() {
			m_currentFrame = 0;
			m_lastUpdateTime = 0.0;
		}

		void setFPS(double fps) {
			m_frameTime = (1000 / fps);
		}
		void setFrameTime(double miliseconds) {
			m_frameTime = miliseconds;
		}

		std::vector<Sprite> animationFrames; // Most preferably inserted in order.
		// std::unordered_map<int, Sprite> animationFFrames //Can be called and inserted at any order.

	private:
		double m_lastUpdateTime = 0.0;
		int m_currentFrame = 0;
		double m_frameTime = 0;
	};

	using AnimationPtr = std::shared_ptr<Animation>;

	class AnimationSet {
		AnimationPtr changeAnimation(const std::string & setName) {
			if (currentAnimation != nullptr)
				currentAnimation->stop();
			return currentAnimation = animSet[setName];
		}

		std::unordered_map<std::string, AnimationPtr> animSet;

	private:
		AnimationPtr currentAnimation = nullptr;
	};
}
