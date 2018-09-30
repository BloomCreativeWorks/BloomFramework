#pragma once

#include "Framework.h"

class TestChar : public bloom::GameObject {
public:
	using bloom::GameObject::GameObject;

	void init(SDL_Rect info = SDL_Rect{ 50,50, 256, 256 }) {
		m_registry.replace<bloom::Position>(m_entity, static_cast<float>(info.x), static_cast<float>(info.y));
		m_registry.assign<bloom::Size>(m_entity, static_cast<float>(info.w), static_cast<float>(info.h));
		auto tmp = m_gameInstance->loadTexture("Assets/TestChar.png", SDL_Color{ 144,168,0,0 });

		m_registry.assign<bloom::Sprite>(m_entity, tmp, SDL_Rect{ 64,96,32,32 });
	}
};