#pragma once
#include "stdIncludes.h"
#include "Sprite.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API Animation {
	public:
		Animation() = default;
		Animation(const std::initializer_list<Sprite>& initList) : animationFrames{ initList } {}
		Animation(const Animation&) = default;
		Animation(Animation&&) = default;
		Animation& operator=(const Animation&) = default;
		Animation& operator=(Animation&&) = default;
		~Animation() = default;

		Sprite update(uint64_t deltaTime);

		void stop() {
			m_currentFrame = 0;
			m_lastUpdateTime = 0;
		}

		void setFrameTime(uint64_t ms) {
			m_frameTime = ms;
		}

		void setFPS(uint64_t fps) {
			setFrameTime(1000 / fps);
		}

		std::vector<Sprite> animationFrames; // Frames must be inserted in order.
		// std::unordered_map<int, Sprite> animationFrames; // Frames can be inserted in any order as long as the correct number is given.

	private:
		uint64_t m_lastUpdateTime = 0;
		size_t m_currentFrame = 0;
		uint64_t m_frameTime = 0;
	};

	using AnimationPtr = std::shared_ptr<Animation>;
}