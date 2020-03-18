#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

class RandomPositionSystem : public bloom::systems::System {
	using Position = bloom::components::Position;
	using bloom::systems::System::DefaultSystem;

public:
	void update(std::optional<double> deltaTime = std::nullopt) override {
		m_registry.view<Position>().each(
			[=](auto entity, Position & pos) {
			if (!m_registry.has<NoRandomPos>(entity)) {
				pos.x = rand() % 672;
				pos.y = rand() % 472;
			}
		});
	}

	void update(int frameWidth, int frameHeight, std::optional<double> dt = std::nullopt)
	{
		m_registry.view<Position>().each(
			[this, frameWidth, frameHeight](auto entity, Position & pos) {
			if (!m_registry.has<NoRandomPos>(entity)) {
				pos.x = rand() % frameWidth;
				pos.y = rand() % frameHeight;
			}
		});
	}
};