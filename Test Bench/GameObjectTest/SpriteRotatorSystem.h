#pragma once
#include "Framework.h"

class SpriteRotatorSystem : public bloom::systems::System {
	using Sprite = bloom::components::Sprite;
	using bloom::systems::System::DefaultSystem;

public:
	void update(std::optional<double> deltaTime = std::nullopt) override {
		m_registry.view<Sprite>().each(
			[&](auto entity, Sprite & spr) {
			auto adjustAmount = rotateSpeed * (deltaTime.value() / 1000);
			spr.rotation = fmod(spr.rotation + adjustAmount, 360);
		});
	}

private:
	double rotateSpeed = static_cast<double>(rand() % 360);
};