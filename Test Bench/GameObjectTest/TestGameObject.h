#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

class TestChar : public bloom::GameObject {
	using Transform = bloom::components::Transform;
	using Position = bloom::Coord;
	using Size = bloom::components::Size;
	using LayerGroup = bloom::components::LayerGroup;
	using Sprite = bloom::components::Sprite;
	using bloom::GameObject::GameObject;

public:
	void init() override {}

	void init(Position pos, Size size, const std::filesystem::path texturePath, std::optional<SDL_Rect> srcRect = std::nullopt, std::optional<Uint32> priority = std::nullopt) {
		
		Transform trans = { pos, 0.0f, size };
		m_registry.assign<Transform>(m_entity, trans);
		auto tmp = m_gameInstance.textures.load(texturePath);
		m_registry.assign<Sprite>(m_entity, tmp, srcRect);

		if (priority != std::nullopt)
			m_registry.assign<LayerGroup>(m_entity, priority.value());
	}

	void disableRandomPos() {
		m_registry.assign<NoRandomPos>(m_entity);
	}

	void enableRandomPos() {
		m_registry.reset<NoRandomPos>(m_entity);
	}
};