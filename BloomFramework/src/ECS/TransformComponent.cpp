#include "..\..\inc\ECS\TransformComponent.h"

inline BloomFramework::TransformComponent::TransformComponent() : position(position.zero()) {}

inline BloomFramework::TransformComponent::TransformComponent(int scale) : position(position.zero()), scale(scale) {}

inline BloomFramework::TransformComponent::TransformComponent(float x, float y) : position(x, y) {}

inline BloomFramework::TransformComponent::TransformComponent(float x, float y, int height, int width, int scale) : position(x, y), height(height), width(width), scale(scale) {}

inline void BloomFramework::TransformComponent::init() { velocity.zero(); }

inline void BloomFramework::TransformComponent::update() {
	position.x += velocity.x * speed;
	position.y += velocity.y * speed;
}
