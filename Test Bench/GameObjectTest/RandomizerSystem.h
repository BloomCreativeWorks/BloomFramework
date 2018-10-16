#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

class RandomPositionSystem : public bloom::systems::System {
	using Position = bloom::components::Position;
	using bloom::systems::System::DefaultSystem;

public:
	void update(std::optional<double> deltaTime = std::nullopt) override;
};

void RandomPositionSystem::update(std::optional<double> deltaTime) {
	m_registry.view<Position>().each(
		[this](auto entity, Position & pos) {
		if (!m_registry.has<NoRandomPos>(entity)) {
			pos.x = rand() % 672;
			pos.y = rand() % 472;
		}
	});
}