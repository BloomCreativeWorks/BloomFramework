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

	using GameObject::GameObject;

public:
	void init(Position pos, Size size, const std::filesystem::path& texturePath, std::optional<SDL_Rect> srcRect, uint32_t priority) {
	}

	void disableRandomPos() {
		registry.assign<NoRandomPos>(entity);
	}

	void enableRandomPos() {
		registry.reset<NoRandomPos>(entity);
	}
};