#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

//using namespace entt;

class TestChar : public bloom::GameObject {
	using Transform = bloom::components::Transform;
	using Position = bloom::Coord;
	using Size = bloom::components::Size;
	using LayerGroup = bloom::components::LayerGroup;
	using Sprite = bloom::components::Sprite;
	template <size_t V>
	using Label = bloom::components::Label<V>;

	using bloom::GameObject::GameObject;

public:
	void init() override {}

	void init(Position pos, Size size, const std::filesystem::path texturePath, std::optional<SDL_Rect> srcRect = std::nullopt, std::optional<Uint32> priority = std::nullopt) {
		
		Transform trans = { pos, 0.0f, size };
		m_registry.assign<Transform>(m_entity, trans);
		auto tmp = m_gameInstance.textures.load(texturePath);
		m_registry.assign<Sprite>(m_entity, tmp, srcRect);

		if (priority != std::nullopt)
			m_registry.assign<LayerGroup>(m_entity, priority.value_or(0));

#pragma warning(push)
#pragma warning(disable: 4307)
		m_registry.assign<Label<static_cast<size_t>("TestObject"_hs)>>(m_entity);
#pragma warning(pop)
	}

	void disableRandomPos() {
		m_registry.assign<NoRandomPos>(m_entity);
	}

	void enableRandomPos() {
		m_registry.reset<NoRandomPos>(m_entity);
	}
};