#pragma once

#include "Framework.h"
#include "RandomComponent.h"

class RandomPositionSystem : public bloom::systems::System {
	using Position = bloom::components::Position;
	using bloom::systems::System::DefaultSystem;

public:
	void update(double = 0) override {
		update(672, 472);
	}

	void update(int frameWidth, int frameHeight, double = 0) {
		m_registry.view<Position, RandomPos>().each(
			[frameWidth, frameHeight](auto, Position& pos, RandomPos&) {
				pos.x = rand() % frameWidth;
				pos.y = rand() % frameHeight;
			}
		);
	}
};