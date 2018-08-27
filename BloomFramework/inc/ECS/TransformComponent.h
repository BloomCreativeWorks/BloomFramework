#pragma once

#include "EntityComponentSystem.h"
#include "../Vector2D.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API TransformComponent : public Component {
	public:
		TransformComponent();
		TransformComponent(int scale);
		TransformComponent(float x, float y);
		TransformComponent(float x, float y, int height, int width, int scale);
		void init() override;

		void update() override;
		
		Vector2D position;
		Vector2D velocity;
		int speed = 3;

		int height = 32;
		int width = 32;
		int scale = 1;
	};
}
