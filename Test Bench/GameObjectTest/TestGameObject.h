#pragma once

#include "Framework.h"
#include "RandomComponent.h"

class TestChar : public bloom::GameObject {
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;
	using Sprite = bloom::components::Sprite;
	using bloom::GameObject::GameObject;

public:
	void init() override {}

	void init(bloom::graphics::TexturePtr texturePtr, SDL_Rect pos_and_size = SDL_Rect{ 50,50, 256, 256 }, std::optional<SDL_Rect> srcRect = std::nullopt) {
		m_registry.replace<Position>(m_entity, pos_and_size.x, pos_and_size.y);
		m_registry.replace<Size>(m_entity, pos_and_size.w, pos_and_size.h);

		m_registry.assign<Sprite>(m_entity, texturePtr, srcRect);
	}

	void init(SDL_Rect pos_and_size = SDL_Rect{ 50,50, 256, 256 }, const std::filesystem::path& texturePath = "Assets/TestChar.png", std::optional<SDL_Rect> srcRect = std::nullopt) {
		auto tmp = c_gameInstance->textures.load(texturePath);
		init(tmp, pos_and_size, srcRect);
	}

	void disableRandomPos() {
		m_registry.reset<RandomPos>(m_entity);
	}

	void enableRandomPos() {
		m_registry.assign<RandomPos>(m_entity);
	}
};