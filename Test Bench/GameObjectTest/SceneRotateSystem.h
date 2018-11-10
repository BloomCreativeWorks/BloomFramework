#pragma once
#include "Framework.h"

class SceneRotateSystem : public bloom::systems::System {
	using Position = bloom::components::Position;
	using bloom::systems::System::DefaultSystem;

public:
	void update(std::optional<double> deltaTime = std::nullopt) override {
		auto adjustValue = rotateSpeed * (deltaTime.value() / 1000);
		parentScene.adjustSceneRotation(adjustValue);
	}

private:
	double rotateSpeed = static_cast<double>(rand() % 360);
};