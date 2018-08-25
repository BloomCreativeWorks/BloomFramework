#pragma once

#include "Components.h"
#include "../Vector2D.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API TransformComponent : public Component {
	public:
		TransformComponent() : position(0.0f, 0.0f) {}
		TransformComponent(float x, float y) : position(x, y) {}
		void init() override {}

		void update() override {
		}
		
		Vector2D position;
	};
}
