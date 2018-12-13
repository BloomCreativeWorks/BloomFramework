#include "Graphics/AnimationSet.h"

namespace bloom::graphics {
	AnimationPtr AnimationSet::changeAnimation(const std::string & setName) {
		AnimationPtr newAnim;
		if (auto it = animSet.find(std::hash_value(setName)); it != animSet.end())
			newAnim = it->second;
		else
			throw Exception("[AnimationSet::changeAnimation] Set doesn't exist");

		if (currentAnimation != newAnim) {
			if(currentAnimation)
				currentAnimation->stop();
			currentAnimation = newAnim;
		}
		return currentAnimation;
	}

	void AnimationSet::addAnimation(const std::string & setName, Animation animation) {
		animSet.try_emplace(std::hash_value(setName), std::make_shared<Animation>(animation));
	}

	void AnimationSet::addAnimation(const std::string & setName, AnimationPtr animationPtr) {
		animSet.try_emplace(std::hash_value(setName), animationPtr);
	}
}