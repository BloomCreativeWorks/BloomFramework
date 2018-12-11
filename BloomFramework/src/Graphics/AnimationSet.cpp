#include "Graphics/AnimationSet.h"

namespace bloom::graphics{
	AnimationPtr AnimationSet::changeAnimation(const std::string & setName) {
		if (currentAnimation)
			currentAnimation->stop();
		return currentAnimation = animSet[std::hash_value(setName)];
	}

	void AnimationSet::addAnimation(const std::string & setName, Animation animation){
		animSet.emplace(std::hash_value(setName), std::make_shared<Animation>(animation));
	}

	void AnimationSet::addAnimation(const std::string & setName, AnimationPtr animationPtr){
		animSet.emplace(std::hash_value(setName), animationPtr);
	}
}