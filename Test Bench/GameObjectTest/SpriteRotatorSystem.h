#pragma once
#include "Framework.h"

class SpriteRotatorSystem : public bloom::systems::DefaultSystem {
	using Sprite = bloom::components::Sprite;
	using bloom::systems::DefaultSystem::System;

public:
	~SpriteRotatorSystem() = default;

	void update(std::optional<double> deltaTime = std::nullopt) override {
		m_registry.view<Sprite>().each(
			[&](auto entity, Sprite & spr) {
			auto adjustAmount = rotateSpeed * (deltaTime.value() / 1000);
			spr.rotationAngle = fmod(spr.rotationAngle + adjustAmount, 360);
		});
	}

private:
	double rotateSpeed = static_cast<double>(rand() % 360);
};