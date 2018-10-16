#include "GameObject.h"

namespace bloom {
	GameObject::GameObject(entt::DefaultRegistry & registry, Game *& gameInstance) : m_registry(registry), m_gameInstance(gameInstance) {
		m_entity = m_registry.create();
		m_registry.assign<Position>(m_entity, 0, 0);
	}

	GameObject::~GameObject() {
		m_registry.destroy(m_entity);
	}

	uint32_t GameObject::getEntityID() {
		return m_entity;
	}
}