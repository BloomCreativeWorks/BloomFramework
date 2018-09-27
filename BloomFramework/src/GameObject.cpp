#include "GameObject.h"

namespace bloom {
	GameObject::GameObject(entt::DefaultRegistry & registry, Game *& gameInstance) : m_registry(registry), m_gameInstance(gameInstance) {
		m_entity = m_registry.create();
		//assignComponent<Position>(50, 50);
		m_registry.assign<Position>(m_entity, 50, 50);
		m_registry.assign<Size>(m_entity, 256, 256);
		auto tmp = m_gameInstance->loadTexture("Assets/TestChar.png", SDL_Color{ 144,168,0,0 });

		m_registry.assign<Sprite>(m_entity, tmp, SDL_Rect{ 64,96,32,32 });
	}

	GameObject::~GameObject() {
		m_registry.destroy(m_entity);
	}
}