#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

class RandomPositionSystem : public bloom::systems::DefaultSystem {
	using Position = bloom::components::Position;
	using bloom::systems::DefaultSystem::System;

public:
	~RandomPositionSystem() = default;

	void update(std::optional<double> deltaTime = std::nullopt) override {
		if (enabled) {
			m_registry.view<Position>().each(
				[this](auto entity, Position & pos) {
				if (!m_registry.has<NoRandomPos>(entity)) {
					pos.x = rand() % 672;
					pos.y = rand() % 472;
				}
			});
		}
	}

	bool enabled = false;
};