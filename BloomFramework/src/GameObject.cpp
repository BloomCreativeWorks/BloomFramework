#include "GameObject.h"

namespace bloom {
	GameObject::GameObject(entt::DefaultRegistry & registry, Game *& game_instance) : registry_(registry), game_instance_(game_instance) {
		entity_ = registry_.create();
		registry_.assign<bloom::Position>(entity_, 0, 0);
	}

	GameObject::~GameObject() {
		registry_.destroy(entity_);
	}

	uint32_t GameObject::getEntityID() {
		return entity_;
	}
}