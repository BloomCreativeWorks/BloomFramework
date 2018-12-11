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

		std::vector<Sprite> animationFrames{}; // Frames must be inserted in order.
		// std::unordered_map<int, Sprite> animationFrames; // Frames can be inserted in any order as long as the correct number is given.
	private:
		double m_lastUpdateTime = 0.0;
		int m_currentFrame = 0;
		double m_frameTime = 0.0; 
	};

	using AnimationPtr = std::shared_ptr<Animation>;
}
