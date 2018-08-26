#pragma once

#include "EntityComponentSystem.h"
#include "../Vector2D.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API TransformComponent : public Component {
	public:
		TransformComponent();
		TransformComponent(int scale) : position(0.0f, 0.0f), scale(scale) {}
		TransformComponent(float x, float y) : position(x, y) {}
		TransformComponent(float x, float y, int height, int width, int scale) : position(x, y), height(height), width(width), scale(scale) {}
		void init() override { velocity = Vector2D(0, 0); }

		void update() override {
			position.x += velocity.x * speed;
			position.y += velocity.y * speed;
		}
		
		Vector2D position;
		Vector2D velocity;
		int speed = 3;

		int height = 32;
		int width = 32;
		int scale = 1;
	};
}
