#include "GameObject.h"

namespace bloom {
	GameObject::GameObject(entt::DefaultRegistry & registry) : m_registry(registry) {
		m_entity = m_registry.create();
	}

	GameObject::~GameObject() {
		m_registry.destroy(m_entity);
	}
}