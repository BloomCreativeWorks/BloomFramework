#pragma once
#include <random>
#include "stdIncludes.h"
#include "Animation.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API AnimationSet {
	public:
		AnimationPtr changeAnimation(const std::string & setName);

		void addAnimation(const std::string & setName, Animation animation);
		void addAnimation(const std::string & setName, AnimationPtr animation);

		std::unordered_map<size_t, AnimationPtr> animSet;

		AnimationPtr getCurrentAnimation() { return currentAnimation; }

	private:
		AnimationPtr currentAnimation = nullptr;
	};
}