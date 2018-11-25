#pragma once
#include "Framework.h"
#include "SceneRotateSystem.h"

class SpriteRotatorSystem : public bloom::systems::DefaultSystem {
	using Transform = bloom::components::Transform;
	using bloom::systems::DefaultSystem::System;

public:
	~SpriteRotatorSystem() = default;

	void update(std::optional<double> deltaTime = std::nullopt) override {
		if (currentRotate != rotateAmount) {
			m_currentAngle += rotateSpeed * (deltaTime.value() / 1000);
			currentRotate = static_cast<int>(m_currentAngle / 360.0);
			currentRotate = static_cast<int>(m_currentAngle / 360.0);
			if (currentRotate == rotateAmount) {
				m_currentAngle = 0.0;
				parentScene.getSystemPtr<SceneRotateSystem>()->rotateAmount = 5;
			}
			m_registry.view<Transform>().each(
				[&](auto entity, Transform & trans) {
				trans.rotation = fmod(m_currentAngle, 360);
			});
		}
	}

	double rotateSpeed = static_cast<double>(rand() % 360);
	int rotateAmount = 5;
	int currentRotate = 0;

private:
	double m_currentAngle = 0.0;
};