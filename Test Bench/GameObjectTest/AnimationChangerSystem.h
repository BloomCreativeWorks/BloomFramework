#pragma once

#include "Framework.h"

/*
 Crap system just to test if shit works, don't mind the hard coded fuckery here.
 Definitely shouldn't be in bloom::systems.
*/

class AnimationChangerSystem : public bloom::systems::System {
	using AnimationSet = bloom::components::AnimationSet;
	using AnimationPtr = bloom::components::AnimationPtr;
	using bloom::systems::System::DefaultSystem;

public:
	void update(double = 0.0) override {
		m_counter = (m_counter + 1) % 100;
		if (m_counter == 0) {
			m_registry.view<AnimationSet>().each(
				[&](auto, AnimationSet& set) {
					set.changeCurrent(c_animations[rand() % 4]);
				}
			);
		}
	}
private:
	int m_counter = 99;
	const std::vector<std::string> c_animations{
		"up",
		"down",
		"left",
		"right"
	};
};