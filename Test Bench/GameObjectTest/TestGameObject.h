#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

class TestChar : public bloom::GameObject {
public:
	using bloom::GameObject::GameObject;

	void init(SDL_Rect pos_and_size = SDL_Rect{ 50,50, 256, 256 }, const std::string & texturePath = "Assets/TestChar.png", std::optional<SDL_Rect> srcRect = std::nullopt, std::optional<Uint32> priority = std::nullopt) {
		m_registry.replace<bloom::Position>(m_entity, pos_and_size.x, pos_and_size.y);
		m_registry.assign<bloom::Size>(m_entity, pos_and_size.w, pos_and_size.h);
		auto tmp = m_gameInstance->textures.load(texturePath);
		m_registry.assign<bloom::Sprite>(m_entity, tmp, srcRect);

		if (priority != std::nullopt)
			m_registry.assign<bloom::Priority>(m_entity, priority.value());
	}
	void disableRandomPos() {
		m_registry.assign<NoRandomPos>(m_entity);
	}
	void enableRandomPos() {
		m_registry.reset<NoRandomPos>(m_entity);
	}
};