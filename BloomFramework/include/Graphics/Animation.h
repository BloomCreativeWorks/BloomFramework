#pragma once
#include "stdIncludes.h"
#include "Sprite.h"


namespace bloom::graphics {
	class BLOOMFRAMEWORK_API Animation {
	public:
		Animation() = default;
		Animation(const std::initializer_list<Sprite> & initList) : animationFrames{ initList } {}
		Animation(const Animation & other) = default;
		Animation(Animation && other) = default;
		Animation& operator=(const Animation & other) = default;
		Animation& operator=(Animation && other) = default;
		~Animation() = default;

		Sprite update(double deltaTime);

		void stop() { m_currentFrame = 0; m_lastUpdateTime = 0.0; }

		void setFPS(double fps) { m_frameTime = (1000.0 / std::fabs(fps)); }
		void setFrameTime(double miliseconds) { m_frameTime = std::fabs(miliseconds); }

		std::vector<Sprite> animationFrames; // Frames must be inserted in order.
		// std::unordered_map<int, Sprite> animationFrames; // Frames can be inserted in any order as long as the correct number is given.
	private:
		double m_lastUpdateTime = 0.0;
		size_t m_currentFrame = 0;
		double m_frameTime = 0.0; 
	};

	using AnimationPtr = std::shared_ptr<Animation>;
}
