#include "GameObject.h"

namespace bloom {
	GameObject::GameObject(entt::DefaultRegistry & registry, Game & gameInstance) : m_registry(registry), m_gameInstance(gameInstance) {
		m_entity = m_registry.create();
	}

	GameObject::~GameObject() {
		if (m_registry.valid(m_entity))
			m_registry.destroy(m_entity);
	}

	uint32_t GameObject::getEntityID() {
		return m_entity;
	}
}