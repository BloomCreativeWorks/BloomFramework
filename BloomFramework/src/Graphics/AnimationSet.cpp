#include "Graphics/AnimationSet.h"

namespace bloom::graphics {
	AnimationPtr AnimationSet::changeAnimation(const std::string & setName) {
		auto it = animSet.find(std::hash_value(setName));
		if (it == animSet.end())
			throw Exception("[AnimationSet::changeAnimation] Set doesn't exist");

		if (currentAnimation != it->second) {
			if(currentAnimation)
				currentAnimation->stop();
			currentAnimation = it->second;
		}
		return currentAnimation;
	}

	void AnimationSet::addAnimation(const std::string & setName, Animation animation) {
		animSet.try_emplace(std::hash_value(setName), std::make_shared<Animation>(animation));
	}

	void AnimationSet::addAnimation(const std::string & setName, AnimationPtr animationPtr) {
		animSet.try_emplace(std::hash_value(setName), animationPtr);
	}
	
	void AnimationSet::removeAnimation(const std::string & setName) {
		animSet.erase(std::hash_value(setName));
	}
	
	void AnimationSet::clearAnimations() { animSet.clear(); }
}