#pragma once

#include "Framework.h"


// Maybe this should be part of bloom::systems?
class AnimationDirectorSystem : public bloom::systems::System {
	using AnimationSet = bloom::components::AnimationSet;
	using AnimationPtr = bloom::components::AnimationPtr;
	using bloom::systems::System::DefaultSystem;

public:
	void update(std::optional<double> deltaTime = std::nullopt) override {
		m_registry.view<AnimationSet, AnimationPtr>().each(
			[&](auto entity, AnimationSet& animSet, AnimationPtr& animPtr) {
				if (animSet.getCurrentAnimation() != animPtr && animSet.getCurrentAnimation()) {
					animPtr->stop();
					animPtr = animSet.getCurrentAnimation();
				}
			}
		);
	}
};