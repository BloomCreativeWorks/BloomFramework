#pragma once

#include "Components.h"
#include "../Vector2D.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API TransformComponent : public Component {
	public:
		TransformComponent() : position(0.0f, 0.0f) {}
		TransformComponent(float x, float y) : position(x, y) {}
		void init() override {velocity = Vector2D(0, 0);}

		void update() override {
			position.x += velocity.x * speed;
			position.y += velocity.y * speed;
		}
		
		Vector2D position;
		Vector2D velocity;
		int speed = 3;
	};
}
