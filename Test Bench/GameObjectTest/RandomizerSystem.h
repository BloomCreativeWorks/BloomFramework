#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

class RandomPositionSystem : public bloom::systems::DefaultSystem {
	using Transform = bloom::components::Transform;
	using bloom::systems::DefaultSystem::System;

public:
	~RandomPositionSystem() = default;

	void update(std::optional<double> deltaTime = std::nullopt) override {
		m_registry.view<Transform>().each(
			[this](auto entity, Transform & trans) {
			if (!m_registry.has<NoRandomPos>(entity)) {
				trans.position.x = rand() % 672;
				trans.position.y = rand() % 472;
			}
		});
	}

	void update(int frameWidth, int frameHeight, std::optional<double> dt = std::nullopt)
	{
		m_registry.view<Transform>().each(
			[this, frameWidth, frameHeight](auto entity, Transform & transform) {
			if (!m_registry.has<NoRandomPos>(entity)) {
				transform.position.x = rand() % frameWidth;
				transform.position.y = rand() % frameHeight;
			}
		});
	}
};