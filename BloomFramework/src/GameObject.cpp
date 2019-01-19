#include "GameObject.h"

namespace bloom {
	GameObject::GameObject(entt::Registry<size_t> & registry, Game & gameInstance) : m_registry(registry), m_gameInstance(gameInstance) {
		m_entity = m_registry.create();
	}

	GameObject::~GameObject() {
		if (m_registry.valid(m_entity))
			m_registry.destroy(m_entity);
	}

	size_t GameObject::getEntityID() {
		return m_entity;
	}
}