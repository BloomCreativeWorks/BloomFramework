#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

class RandomPositionSystem : public bloom::systems::System {
	using Position = bloom::components::Position;
	using bloom::systems::System::DefaultSystem;

public:
	void update(double = 0.0) override {
		update(672, 472);
	}

	void update(int frameWidth, int frameHeight, double = 0.0) {
		m_registry.view<Position>().each(
			[this, frameWidth, frameHeight](auto entity, Position& pos) {
			if (!m_registry.has<NoRandomPos>(entity)) {
				pos.x = rand() % frameWidth;
				pos.y = rand() % frameHeight;
			}
		});
	}
};