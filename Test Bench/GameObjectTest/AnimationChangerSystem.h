#pragma once

#include "Framework.h"

/*
 Crap system just to test if shit works, don't mind the hard coded fuckery here.
 Definitely shouldn't be in bloom::systems.
*/

class AnimationChangerSystem : public bloom::systems::System {
	using AnimationSet = bloom::components::AnimationSet;
	using AnimationPtr = bloom::components::AnimationPtr;
	using bloom::systems::System::System;

public:
	void update(std::optional<double> deltaTime = std::nullopt) override {
		counter = (counter + 1) % 100;
		if (counter == 0) {
			m_registry.view<AnimationSet>().each(
				[&](auto entity, AnimationSet& animSet) {
					animSet.changeCurrent(animations[rand() % 4]);
				}
			);
		}
	}
private:
	int counter = 99;
	std::vector<std::string> animations{
		"up",
		"down",
		"left",
		"right"
	};
};