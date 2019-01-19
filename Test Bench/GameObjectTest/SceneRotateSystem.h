#pragma once
#include "Framework.h"
#include "RandomizerSystem.h"

class SceneRotateSystem : public bloom::systems::DefaultSystem {
	using Position = bloom::components::Position;
	using bloom::systems::DefaultSystem::System;

public:
	~SceneRotateSystem() = default;

	void update(std::optional<double> deltaTime = std::nullopt) override {
		if (currentRotate != rotateAmount) {
			m_currentAngle += rotateSpeed * (deltaTime.value_or(0.0) / 1000);
			currentRotate = static_cast<int>(m_currentAngle / 360.0);
			if (currentRotate == rotateAmount) {
				m_currentAngle = 0.0;
				parentScene.getSystemPtr<RandomPositionSystem>()->enabled = true;
			}
			parentScene.setSceneRotation(m_currentAngle);
		}
	}

	double rotateSpeed = static_cast<double>(rand() % 360);
	int rotateAmount = 0;
	int currentRotate = 0;

private:
	double m_currentAngle = 0.0;
	
};