#include "GameObject.h"

namespace bloom {
	GameObject::GameObject(entt::DefaultRegistry & registry) : m_registry(registry) {
		m_entity = m_registry.create();
		m_registry.assign<Position>(m_entity, 0.0f, 0.0f); // This is a must-have in most cases.
	}
	GameObject::~GameObject()
	{
		m_registry.destroy(m_entity);
	}
}