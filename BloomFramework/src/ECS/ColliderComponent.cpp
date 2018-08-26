#include "..\..\inc\ECS\ColliderComponent.h"

void BloomFramework::ColliderComponent::init() {
	if(!entity->hasComponent<TransformComponent>())
		entity->addComponent<TransformComponent>();

	transform = &entity->getComponent<TransformComponent>();
}

void BloomFramework::ColliderComponent::update() {
	collider.x = static_cast<int>(transform->position.x);
	collider.y = static_cast<int>(transform->position.y);

	collider.w = transform->width * transform->scale;
	collider.h = transform->height * transform->scale;
}
