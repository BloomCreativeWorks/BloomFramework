#pragma once

#include "Framework.h"

class TestChar : public bloom::GameObject {
public:
	using bloom::GameObject::GameObject;

	void init() {
		m_registry.replace<bloom::Position>(m_entity, 50.0f, 50.0f);
		m_registry.assign<bloom::Size>(m_entity, 256, 256);
		auto tmp = m_gameInstance->loadTexture("Assets/TestChar.png", SDL_Color{ 144,168,0,0 });

		m_registry.assign<bloom::Sprite>(m_entity, tmp, SDL_Rect{ 64,96,32,32 });
	}
};