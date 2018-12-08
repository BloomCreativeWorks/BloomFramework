#pragma once
#include "stdIncludes.h"
#include "Sprite.h"


namespace bloom::graphics {
	class BLOOMFRAMEWORK_API Animation {
	public:
		Sprite update(double deltaTime);

		void stop();

		void setFPS(double fps);
		void setFrameTime(double miliseconds);

		std::vector<Sprite> animationFrames{}; // Most preferably inserted in order.
		// std::unordered_map<int, Sprite> animationFFrames //Can be called and inserted at any order.
	private:
		double m_lastUpdateTime = 0.0f;
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
