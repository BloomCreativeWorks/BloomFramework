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
	template <uint64_t V>
	using Label = bloom::components::Label<V>;

	using bloom::GameObject::GameObject;

public:
	void init(Position pos, Size size, const std::filesystem::path& texturePath, std::optional<SDL_Rect> srcRect, uint32_t priority) {
		
		Transform trans = { pos, 0.0f, size };
		m_registry.assign<Transform>(m_entity, trans);
		auto tmp = m_gameInstance.textures.load(texturePath);
		m_registry.assign<Sprite>(m_entity, tmp, srcRect);

		m_registry.assign<LayerGroup>(m_entity, priority);

#pragma warning(push)
#pragma warning(disable: 4307)
		m_registry.assign<Label<"TestObject"_hs>>(m_entity);
#pragma warning(pop)
	}

	void disableRandomPos() {
		m_registry.assign<NoRandomPos>(m_entity);
	}

	void enableRandomPos() {
		m_registry.reset<NoRandomPos>(m_entity);
	}
};