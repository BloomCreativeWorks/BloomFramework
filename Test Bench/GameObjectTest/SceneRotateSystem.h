#pragma once
#include "Framework.h"

class SceneRotateSystem : public bloom::systems::System {
	using Position = bloom::components::Position;
	using bloom::systems::System::DefaultSystem;

public:
	void update(std::optional<double> deltaTime = std::nullopt) override {
		auto adjustValue = 60.0 * (deltaTime.value() / 1000);
		parentScene.adjustSceneRotation(adjustValue);
	}
};