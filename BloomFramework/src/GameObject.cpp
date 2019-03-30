#include "GameObject.h"

namespace bloom {
	GameObject::GameObject(entt::DefaultRegistry& registry, Game& gameInstance) :
		registry(registry),
		gameInstance(gameInstance),
		entity(registry.create())
	{}

	GameObject::~GameObject() {
		if (registry.valid(entity))
			registry.destroy(entity);
	}
}